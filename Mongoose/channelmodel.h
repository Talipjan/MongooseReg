#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
#include <QPointF>
#include <QPoint>
#include <QtCharts/QAbstractSeries>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "chelement.h"
#include "areadraw.h"

QT_CHARTS_USE_NAMESPACE

class ChannelModel : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QQmlListProperty<ChElement> data     READ data                       NOTIFY dataChanged)
   Q_PROPERTY(QQmlListProperty<AreaDraw>  area     READ area                       NOTIFY areaChanged)
   Q_PROPERTY(                   QString  name     READ name     WRITE setName     NOTIFY nameChanged)
   Q_PROPERTY(                   QString  driver   READ driver   WRITE setDriver   NOTIFY driverChanged)
   Q_PROPERTY(                       int  numarea  READ numarea  WRITE setNumarea  NOTIFY numareaChanged)
   Q_PROPERTY(                     qreal  pagesize READ pagesize WRITE setPagesize NOTIFY pagesizeChanged)
   Q_PROPERTY(                     qreal  pageval  READ pageval  WRITE setPageval  NOTIFY pagevalChanged)
   Q_PROPERTY(              QVector<int>  deep     READ deep                       NOTIFY deepChanged)
   Q_PROPERTY(              QVector<int>  time     READ time                       NOTIFY timeChanged)
   Q_PROPERTY(              QVector<int>  dataue   READ dataue                     NOTIFY dataueChanged)
   Q_CLASSINFO("DefaultProperty", "data")
public:
   ChannelModel(QObject *parent = 0);

   QQmlListProperty<ChElement> data();
   QQmlListProperty<AreaDraw>  area();

   Q_INVOKABLE void add();
   Q_INVOKABLE void addReadyElement(ChElement *element);
   Q_INVOKABLE void delElement(int index);
   Q_INVOKABLE void addArea();
   Q_INVOKABLE void addReadyArea(AreaDraw *area);
   Q_INVOKABLE void delArea(int index);

   QString name() const;
   QString driver() const;
   int numarea() const;
   qreal pagesize() const;
   qreal pageval() const;

   QVector<int> deep()   const;
   QVector<int> time()   const;
   QVector<int> dataue() const;
signals:
   void dataChanged();
   void areaChanged();
   void driverChanged(QString driver);
   void nameChanged(QString name);
   void dataueChanged();
   void deepChanged();
   void timeChanged();
   void numareaChanged(int);
   void pagesizeChanged(qreal);
   void pagevalChanged(qreal);
public slots:
   void setName(const QString &);
   void setDriver(const QString &);
   void setNumarea(const int &);
   void setData(const QVector<int>);
   void update(QAbstractSeries *series);
   void openFile(QString file);
   void saveFile(QString file);
   void parseXML( QXmlStreamReader &xml);
   void ResizeArea();
   void setSizeArea(int index,qreal scale);
   void setPagesize(const qreal &n);
   void setPageval(const qreal &n);
private:
   static void appendData(QQmlListProperty<ChElement> *list, ChElement *value);
   static int countData(QQmlListProperty<ChElement> *list);
   static ChElement *atData(QQmlListProperty<ChElement> *list, int index);
   static void clearData(QQmlListProperty<ChElement> *list);

   static void appendArea(QQmlListProperty<AreaDraw> *list, AreaDraw *value);
   static int countArea(QQmlListProperty<AreaDraw> *list);
   static AreaDraw *atArea(QQmlListProperty<AreaDraw> *list, int index);
   static void clearArea(QQmlListProperty<AreaDraw> *list);

   QList<ChElement*> m_data;     //каналы
   QList<AreaDraw*>  m_area;     //дорожки
   QVector<int>      m_Deep;     //глубина
   QVector<int>      m_Time;     //время
   QVector<int>      m_DataUE;   //данные с прибора по каналам
   QString           m_name;     //имя планшета
   QString           m_driver;   //имя драйвера
   int               m_numch;    //количество каналов
   int               m_numarea;  //количество дорожек
   qreal             m_pagesize; //длина дорожки
   qreal             m_pageval;  //текущий максимум на дорожке ось y
};


#endif // CHANNELMODEL_H
