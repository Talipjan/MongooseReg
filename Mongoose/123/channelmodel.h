#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
#include <QPointF>
#include <QPoint>
#include "chelement.h"

class ChannelModel : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QQmlListProperty<ChElement> data     READ data               NOTIFY dataChanged)
   Q_PROPERTY(                   QString  name     READ name WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(           QVector<QPoint>  deeptime READ deeptime )
   Q_PROPERTY(              QVector<int>  dataue   READ dataue             NOTIFY dataueChanged)
   Q_CLASSINFO("DefaultProperty", "data")
public:
   ChannelModel(QObject *parent = 0);

   QQmlListProperty<ChElement> data();

   Q_INVOKABLE void add();
   QString name() const;

   QVector<QPoint> deeptime() const;
   QVector<int>    dataue()   const;
signals:
   void dataChanged();
   void nameChanged(QString name);
   void dataueChanged(QVector<int> dataue);
public slots:
   void setName(const QString &);
   void setData(const QVector<int>);
private:
   static void appendData(QQmlListProperty<ChElement> *list, ChElement *value);
   static int countData(QQmlListProperty<ChElement> *list);
   static ChElement *atData(QQmlListProperty<ChElement> *list, int index);
   static void clearData(QQmlListProperty<ChElement> *list);

   QList<ChElement*> m_data;     //каналы
   QVector<QPoint>   m_DeepTime; //глубина время
   QVector<int>      m_DataUE;   //данные с прибора по каналам
   QString           m_name;
   int               m_numch;
};


#endif // CHANNELMODEL_H
