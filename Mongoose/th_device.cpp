#include "th_device.h"
#include <QMessageBox>
#include <QTimer>
#include "channelmodel.h"
#include "chelement.h"

Th_device::Th_device(QObject *parent):
   QThread(parent)
{
   stop=0;wrDev=0;
   handle_device=NULL;
   BusyW=0;
   curPack=0;
   //crc32_init();
   ThConnectHid();
   erPack=0;
   HaveKf=0;
   m_data.resize(64);

   m_ChannelModel = new ChannelModel;
   connect(this, SIGNAL(ThDataReadyHid(QVector<int>)), m_ChannelModel, SLOT(setData(const QVector<int>)));

   QTimer *timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
   timer->start(100);
}

ChannelModel* Th_device::getChannelModel()
{
   return m_ChannelModel;
}

void Th_device::updateTimer()
{
   m_count++;
   m_data[0] = m_data[1] = m_count;
   for(int i=2;i<32;i++)
   {
      m_data[i] = rand();
   }
   emit ThDataReadyHid(m_data);
   //QMessageBox::information(0, "Information", "Information message text");
}
//-----------------------------------------------------
void Th_device::ThConnectHid()
{
   QString product_string("BDGauge");

   //if(handle_device)
   {
      hid_close(handle_device);
   }
   handle_device=NULL;
   emit ThMess(AClear);
   erPack=0;
   HaveKf=0;
   HaveSt=0;

   struct hid_device_info *devs, *cur_dev;
   /* запускаем поиск hid-устройств*/
   devs = hid_enumerate(/*VID*/0x0483, /*PID*/0x5750);

   /*все найдённые устройства помещаются в динамический список*/
   cur_dev = devs;
   while (cur_dev)
   {
      emit CurDevice(QString::fromWCharArray(cur_dev->product_string));
      /*пытаемся найти устройство с заданной строкой описания продукта*/
      if (QString::fromWCharArray(cur_dev->product_string) == product_string)
         break;
      cur_dev = cur_dev->next;
   }


   if (cur_dev)
   {
      //emit CurDevice("Устройство найдено");
      handle_device = hid_open_path(cur_dev->path);
      hid_set_nonblocking(handle_device, 1);
      // Открытие устройства, используя VID, PID,
      // и опционально серийный номер.
      //handle_device = hid_open(0x0483, 0x5750, NULL);


      if (handle_device!=NULL)
      {
         //emit CurDevice("Устройство подключено");
         /*то активируем кнопку*/
         emit ThMess(AConnect);
         //ReadKF();
      }
      else
         emit ThMess(EConnect);
   }

   /*если нашли нужное устройство, и оно успешно открылось...
    if (cur_dev && (handle_device = hid_open_path(cur_dev->path)))
    {*/

   /*то активируем кнопку
      emit ThMess(AConnect);

    }
    else
        emit ThMess(EConnect);*/

   /*удаляем список*/
   hid_free_enumeration(devs);
   wait(5000);
}

//-----------------------------------------------------
void Th_device::ThDisconnectHid()
{
   hid_close(handle_device);
}
//-----------------------------------------------------
void Th_device::ThWriteHid(unsigned char* Data)
{

}
//-----------------------------------------------------
void Th_device::ThStop()
{
   stop=1;
}
void ThDone();
//-----------------------------------------------------
void Th_device::ThDone()
{
   stop=1;
   wait(5000);
   terminate();
}
//-----------------------------------------------------
void Th_device::FlagWR(bool)
{

}
//-----------------------------------------------------

uint Th_device::Crc32(uint Crc, uint Data)
{
   int i;

   Crc = Crc ^ Data;

   for(i=0; i<32; i++)
      if (Crc & 0x80000000)
         Crc = (Crc << 1) ^ 0x04C11DB7; // Polynomial used in STM32
      else
         Crc = (Crc << 1);

   return(Crc);
}
//-----------------------------------------------------
uint Th_device::Crc32Fast(uint Crc, uint Data)
{
   static const uint CrcTable[16] = { // Nibble lookup table for 0x04C11DB7 polynomial
                                      0x00000000,0x04C11DB7,0x09823B6E,0x0D4326D9,0x130476DC,0x17C56B6B,0x1A864DB2,0x1E475005,
                                      0x2608EDB8,0x22C9F00F,0x2F8AD6D6,0x2B4BCB61,0x350C9B64,0x31CD86D3,0x3C8EA00A,0x384FBDBD };

   Crc = Crc ^ Data; // Apply all 32-bits

   // Process 32-bits, 4 at a time, or 8 rounds

   Crc = (Crc << 4) ^ CrcTable[Crc >> 28]; // Assumes 32-bit reg, masking index to 4-bits
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28]; //  0x04C11DB7 Polynomial used in STM32
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];
   Crc = (Crc << 4) ^ CrcTable[Crc >> 28];

   return(Crc);
}

//-----------------------------------------------------
void Th_device::run()
{
   int  Result;
   uchar CRC_t;
   //struct hid_device_info *devs, *cur_dev;


   while(!stop)
   {

      /* запускаем поиск hid-устройств*/
      //      if(!hid_enumerate(/*VID*/0x0483, /*PID*/0x5750))
      //      {
      //         emit ThMess(EConnect);
      //         ThConnectHid();
      //      }


      //      if(handle_device)
      //      {
      //         //emit ThMess(4);
      //         Result = hid_read_timeout(handle_device, InputReport, 64, 100);  //ждем данных от устройства 10 мс
      //         if(Result)
      //         {
      //            //erPack=0;
      //            //InputReport[6]=(uchar)(Crc32Fast(0xFFFFFFFF,( ((uint)InputReport[2])<<24) +( ((uint)InputReport[3])<<16) +( ((uint)InputReport[4])<<8) +((uint)InputReport[5])));//crc32(0,InputReport+2,4));
      //            CRC_t=(uchar)(Crc32Fast(0xFFFFFFFF,( ((uint)InputReport[2])<<24) +( ((uint)InputReport[3])<<16) +( ((uint)InputReport[4])<<8) +((uint)InputReport[5])));

      //            if(CRC_t==InputReport[11])
      //            {
      //               emit ThMess(4);
      //               emit ThReadHid(InputReport);
      //            }
      //         }
      //      }
      //      else
      //      {
      //         //wait(1000);
      //         emit ThMess(EConnect);
      //         ThConnectHid();
      //      }
   }

   ThDisconnectHid();
}
//-----------------------------------------------------

