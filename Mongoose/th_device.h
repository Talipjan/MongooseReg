#ifndef TH_DEVICE_H
#define TH_DEVICE_H

#include <QObject>
#include <QThread>
#include <QVector>
#include "hidapi.h"
#include "channelmodel.h"

#define CPack    19

#define CRC32_POLY   0x04C11DB7
#define CRC32_POLY_R 0xEDB88320

#define EConnect 1
#define AConnect 2
#define AClear   3


#define ErCount  30

class Th_device : public QThread
{
   Q_OBJECT
public:
   explicit Th_device(QObject *parent = 0);
   ChannelModel* getChannelModel();
private:
   hid_device *handle_device; /*указатель на структуру,описывающую HID-устройство в HIDAPI*/
   volatile bool stop,wrDev,BusyW,HaveKf,HaveSt;
   int curPack,erPack;
   unsigned char InputReport[64],WRReport[64],DataSend[64];
   float kf_d[8];
   uchar st_d[4];
   uchar Mt,Kt,Ms,Ks;
   QVector<int> m_data;
   int m_count = 0;
   uint Crc32(uint Crc, uint Data);
   uint Crc32Fast(uint Crc, uint Data);

   ChannelModel *m_ChannelModel;

   void run();
public slots:
   void ThConnectHid();
   void ThDisconnectHid();
   void ThWriteHid(unsigned char *Data);
   void ThStop();
   void ThDone();
   void FlagWR(bool);
   void updateTimer();
signals:
   void ThReadHid(unsigned char* Data);
   void ThDataReadyHid(QVector<int>);
   void ThWrRecHid(unsigned char* Data);
   void ThMess(int);
   void CurDevice(QString);
};

#endif // TH_DEVICE_H
