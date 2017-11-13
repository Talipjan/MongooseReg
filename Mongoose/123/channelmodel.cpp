
#include "channelmodel.h"

ChannelModel::ChannelModel(QObject *parent):QObject(parent)
{
   m_name = "Mongoose";
   //m_DeepTime.resize(64);
   m_DataUE.resize(64);
   m_numch = 32;

   ChElement *element = new ChElement(this);
   element->setProperty("color", "lightgreen");
   element->setProperty("text", "1");

   m_data << element;

   element = new ChElement(this);
   element->setProperty("color", "lightgreen");
   element->setProperty("text", "2");

   m_data << element;

   element = new ChElement(this);
   element->setProperty("color", "lightgreen");
   element->setProperty("text", "3");

   m_data << element;
}
//---------------------------------------------------------------------------------------------
QQmlListProperty<ChElement> ChannelModel::data()
{
   return QQmlListProperty<ChElement>(static_cast<QObject *>(this), static_cast<void *>(&m_data),
                                      &ChannelModel::appendData, &ChannelModel::countData,
                                      &ChannelModel::atData, &ChannelModel::clearData);
}

void ChannelModel::add()
{
   ChElement *element = new ChElement(this);
   element->setProperty("color", "skyblue");
   element->setProperty("text", "new");
   m_data.append(element);

   emit dataChanged();
}

void ChannelModel::appendData(QQmlListProperty<ChElement> *list, ChElement *value)
{
   QList<ChElement*> *data = static_cast<QList<ChElement*> *>(list->data);
   data->append(value);
}

int ChannelModel::countData(QQmlListProperty<ChElement> *list)
{
   QList<ChElement*> *data = static_cast<QList<ChElement*> *>(list->data);
   return data->size();
}

ChElement *ChannelModel::atData(QQmlListProperty<ChElement> *list, int index)
{
   QList<ChElement*> *data = static_cast<QList<ChElement*> *>(list->data);
   return data->at(index);
}

void ChannelModel::clearData(QQmlListProperty<ChElement> *list)
{
   QList<ChElement*> *data = static_cast<QList<ChElement*> *>(list->data);
   qDeleteAll(data->begin(), data->end());
   data->clear();
}
//---------------------------------------------------------------------------------------------
QString ChannelModel::name() const
{
   return m_name;
}

void ChannelModel::setName(const QString &n)
{
   m_name = n;
   emit nameChanged(m_name);
}
//---------------------------------------------------------------------------------------------
QVector<QPoint> ChannelModel::deeptime() const
{
   return m_DeepTime;
}
QVector<int>    ChannelModel::dataue()   const
{
   return m_DataUE;
}
//---------------------------------------------------------------------------------------------
void ChannelModel::setData(const QVector<int> data)
{
   QString str_data;
   // первые два это время и глубина остальные каналы
   m_DeepTime.append(QPoint(data[0],data[1]));
   // сохраняем текущие показания прибора
   m_DataUE = data.mid(2);
   for(int i=0;i<m_numch;i++)
   {
      //Добавить преобразование к знаковому и беззнаковому
      str_data += QString("var k%1 = %2;\n").arg(i+1).arg(data[i]);
   }
}
