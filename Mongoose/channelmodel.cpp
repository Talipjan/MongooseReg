#include "channelmodel.h"
#include <QMessageBox>
#include <QListIterator>
#include <QFile>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>

QT_CHARTS_USE_NAMESPACE

ChannelModel::ChannelModel(QObject *parent):QObject(parent)
{
   m_name = "Mongoose";
   m_pagesize = 40;
   //m_DeepTime.resize(64);
   m_DataUE.resize(64);
   m_numch = 32;
   m_numarea = 2;
   m_Time.append(0);
   m_Deep.append(0);

   AreaDraw *area = new AreaDraw(this);
   area->setProperty("name","Дорожка 1");
   area->setProperty("width","30");
   area->setProperty("begin","0");
   m_area << area;

   area = new AreaDraw(this);
   area->setProperty("name","Дорожка 2");
   area->setProperty("width","30");
   area->setProperty("begin","30");
   m_area << area;

   area = new AreaDraw(this);
   area->setProperty("name","Дорожка 3");
   area->setProperty("width","40");
   area->setProperty("begin","60");
   m_area << area;

   ChElement *element = new ChElement(this);
   element->setProperty("color", "blue");
   element->setProperty("text", "Температура");
   element->setProperty("convert", "k1");
   element->setProperty("area", "1");
   element->setProperty("diva", "0.5");

   m_data << element;

   element = new ChElement(this);
   element->setProperty("color", "lightgreen");
   element->setProperty("text", "Давление");
   element->setProperty("convert", "k2*2");
   element->setProperty("area", "2");
   element->setProperty("diva", "4");

   m_data << element;

   //   element = new ChElement(this);
   //   element->setProperty("color", "orange");
   //   element->setProperty("text", "3");
   //   element->setProperty("convert", "k3");

   //   m_data << element;
}
//---------------------------------------------------------------------------------------------
QQmlListProperty<ChElement> ChannelModel::data()
{
   return QQmlListProperty<ChElement>(static_cast<QObject *>(this), static_cast<void *>(&m_data),
                                      &ChannelModel::appendData, &ChannelModel::countData,
                                      &ChannelModel::atData, &ChannelModel::clearData);
}
void ChannelModel::addReadyElement(ChElement *element)
{
   int j=0;

   QListIterator<ChElement*> it_data(m_data);
   while (it_data.hasNext())
   {
      if(it_data.next()->area()==element->area())
      {
         j++;
      }
   }
   element->setAreaindex(j);
   m_data.append(element);
   emit dataChanged();
}
void ChannelModel::add()
{
   QString str;
   int j=0;
   //ChElement *element_area;
   ChElement *element = new ChElement(this);
   element->setProperty("color", str.sprintf("#%02X%02X%02X",rand()%256 + 1,rand()%256 + 1,rand()%256 + 1));
   //QMessageBox::information(0, "Information", str);
   element->setProperty("text", "new");
   element->setProperty("convert", "k" + QString("%1").arg(m_data.size() + 1));
   element->SetData(m_Deep.size());
   element->setProperty("area", "1");
   QListIterator<ChElement*> it_data(m_data);
   while (it_data.hasNext())
   {
      if(it_data.next()->area()==element->area())
      {
         j++;
      }
   }
   element->setAreaindex(j);
   m_data.append(element);

   emit dataChanged();
}

void ChannelModel::delElement(int index)
{
   m_data.removeAt(index);
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
QQmlListProperty<AreaDraw> ChannelModel::area()
{
   return QQmlListProperty<AreaDraw>(static_cast<QObject *>(this), static_cast<void *>(&m_area),
                                      &ChannelModel::appendArea, &ChannelModel::countArea,
                                      &ChannelModel::atArea, &ChannelModel::clearArea);
}

void ChannelModel::addReadyArea(AreaDraw *area)
{
   m_area.append(area);
   ResizeArea();
   emit areaChanged();
}
void ChannelModel::addArea()
{
   AreaDraw *area = new AreaDraw(this);

   area->setProperty("name", "Дорожка " + QString("%1").arg(m_area.size()+1));
   area->setProperty("width","10");
   m_area.append(area);
   ResizeArea();
   emit areaChanged();
}

void ChannelModel::delArea(int index)
{
   m_area.removeAt(index);
   ResizeArea();
   emit areaChanged();
}

void ChannelModel::appendArea(QQmlListProperty<AreaDraw> *list, AreaDraw *value)
{
   QList<AreaDraw*> *data = static_cast<QList<AreaDraw*> *>(list->data);
   data->append(value);
}

int ChannelModel::countArea(QQmlListProperty<AreaDraw> *list)
{
   QList<AreaDraw*> *data = static_cast<QList<AreaDraw*> *>(list->data);
   return data->size();
}

AreaDraw *ChannelModel::atArea(QQmlListProperty<AreaDraw> *list, int index)
{
   QList<AreaDraw*> *data = static_cast<QList<AreaDraw*> *>(list->data);
   return data->at(index);
}

void ChannelModel::clearArea(QQmlListProperty<AreaDraw> *list)
{
   QList<AreaDraw*> *data = static_cast<QList<AreaDraw*> *>(list->data);
   qDeleteAll(data->begin(), data->end());
   data->clear();
}

void ChannelModel::ResizeArea()
{
   qreal scale = 0;
   if(m_area.size()>0)
   {
      for(int i=0;i<m_area.size();i++)
      {
         scale += m_area[i]->width();
      }
      if(scale>100)
      {
         scale = 100.0/scale;
         for(int i=0;i<m_area.size();i++)
         {
            m_area[i]->setWidth(scale*m_area[i]->width());
         }
      }
      m_area[0]->setBegin(0);
      for(int i=1;i<m_area.size();i++)
      {
         m_area[i]->setBegin(m_area[i-1]->begin() + m_area[i-1]->width());
      }
   }
}

void ChannelModel::setSizeArea(int index,qreal scale)
{
   qreal div = 0;
   if(m_area.size()>0)
   {
      m_area[index]->setWidth(scale);
      for(int i=0;i<m_area.size();i++)
      {
         if(index!=i)
         {
            div += m_area[i]->width();
         }
      }
      if(div>100-scale)
      {
         div = (100.0-scale)/div;
         for(int i=0;i<m_area.size();i++)
         {
            if(index!=i)
            {
               m_area[i]->setWidth(div*m_area[i]->width());
            }
         }
      }
      m_area[0]->setBegin(0);
      for(int i=1;i<m_area.size();i++)
      {
         m_area[i]->setBegin(m_area[i-1]->begin() + m_area[i-1]->width());
      }
   }
   emit areaChanged();
}
//---------------------------------------------------------------------------------------------
void ChannelModel::openFile(QString file)
{
   QXmlStreamAttributes attributes;
   ChElement *element;
   AreaDraw *area;

   QFile* hfile = new QFile(file);
   if (!hfile->open(QIODevice::ReadOnly | QIODevice::Text))
   {
      //return false;
      QMessageBox::information(0, "Information", "str");
   }
   m_data.clear();
   m_area.clear();
   QXmlStreamReader xml(hfile);
   while (!xml.atEnd() && !xml.hasError())
   {
      QXmlStreamReader::TokenType token = xml.readNext();
      if (token == QXmlStreamReader::StartDocument)
      {
         //QMessageBox::information(0, "Information", xml.name().toString());
         continue;
      }
      if (token == QXmlStreamReader::StartElement)
      {
         if (xml.name() == "planshet")
            continue;
         if (xml.name() == "name")
         {
            m_name = xml.readElementText();
         }
         if (xml.name() == "driver")
         {
            m_driver = xml.readElementText();
         }
         if (xml.name() == "numarea")
         {
            m_numarea = xml.readElementText().toInt();
         }
         if (xml.name() == "pagesize")
         {
            m_pagesize = xml.readElementText().toFloat();
         }
         if (xml.name() == "chelement")
         {
            attributes = xml.attributes();
            if (attributes.hasAttribute("id"))
            {
               //ui->textEdit->append(" id: " + attributes.value("id") + "\n");
               element = new ChElement(this);
               element->parseXML(xml);
            }
            if(xml.tokenType() == QXmlStreamReader::EndElement)
            {
               m_data.append(element);
            }
         }
         if (xml.name() == "drawarea")
         {
            attributes = xml.attributes();
            if (attributes.hasAttribute("id"))
            {
               area = new AreaDraw(this);
               area->parseXML(xml);
            }
            if(xml.tokenType() == QXmlStreamReader::EndElement)
            {
               m_area.append(area);
            }
         }
      }
   }
   //ResizeArea();
   emit dataChanged();
}

void ChannelModel::parseXML( QXmlStreamReader &xml)
{
   ChElement *element;

   QXmlStreamAttributes attributes = xml.attributes();
   if (attributes.hasAttribute("id"))
   {
      //ui->textEdit->append(" id: " + attributes.value("id") + "\n");
      element = new ChElement(this);
   }
   xml.readNext();
   while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "chelement"))
   {
      if(element)
      {
         if (xml.tokenType() == QXmlStreamReader::StartElement)
         {
            if(xml.name()=="name")
            {
               element->setProperty("name", xml.readElementText());
            }
            if(xml.name()=="color")
            {
               element->setProperty("color", xml.readElementText());
            }
            if(xml.name()=="text")
            {
               element->setProperty("text", xml.readElementText());
            }
            if(xml.name()=="unit")
            {
               element->setProperty("unit", xml.readElementText());
            }
            if(xml.name()=="convert")
            {
               element->setProperty("convert", xml.readElementText());
            }
            if(xml.name()=="diva")
            {
               element->setProperty("diva", xml.readElementText());
            }
            if(xml.name()=="begpoint")
            {
               element->setProperty("begpoint", xml.readElementText());
            }
            if(xml.name()=="wrpoint")
            {
               element->setProperty("wrpoint", xml.readElementText());
            }
            if(xml.name()=="decpl")
            {
               element->setProperty("decpl", xml.readElementText());
            }
            if(xml.name()=="area")
            {
               element->setProperty("area", xml.readElementText());
            }
         }
      }
      xml.readNext();
   }
   if(xml.tokenType() == QXmlStreamReader::EndElement)
   {
      m_data.append(element);
   }
}

void ChannelModel::saveFile(QString file)
{
   QFile* hfile = new QFile(file);
   QString srt;
   int j=0;

   hfile->open(QIODevice::WriteOnly);
   /* Создаем объект, с помощью которого осуществляется запись в файл */
   QXmlStreamWriter xmlWriter(hfile);
   xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
   xmlWriter.writeStartDocument();     // Запускаем запись в документ
   xmlWriter.writeStartElement("planshet");   // Записываем первый элемент с его именем

   xmlWriter.writeStartElement("name");//name
   xmlWriter.writeCharacters(m_name);
   xmlWriter.writeEndElement();        //name

   xmlWriter.writeStartElement("driver");//driver
   xmlWriter.writeCharacters(m_driver);
   xmlWriter.writeEndElement();          //driver

   xmlWriter.writeStartElement("numarea");//numarea
   xmlWriter.writeCharacters(QString("%1").arg(m_numarea));
   xmlWriter.writeEndElement();          //numarea

   xmlWriter.writeStartElement("pagesize");//pagesize
   xmlWriter.writeCharacters(QString("%1").arg(m_pagesize));
   xmlWriter.writeEndElement();          //pagesize

   j=0;
   AreaDraw *area;
   QListIterator<AreaDraw*> it_area(m_area);
   while (it_area.hasNext())
   {
      area = it_area.next();
      xmlWriter.writeStartElement("drawarea");//drawarea
      xmlWriter.writeAttribute("id",QString("%1").arg(j));
      area->saveXML(xmlWriter);
      xmlWriter.writeEndElement();//drawarea
      j++;
   }

   j=0;
   ChElement *element;
   QListIterator<ChElement*> it_data(m_data);
   while (it_data.hasNext())
   {
      element = it_data.next();
      xmlWriter.writeStartElement("chelement");//chelement
      xmlWriter.writeAttribute("id",QString("%1").arg(j));
      element->saveXML(xmlWriter);
      xmlWriter.writeEndElement();//chelement

      j++;
   }

   xmlWriter.writeEndElement(); //planshet
   xmlWriter.writeEndDocument();
   hfile->close();   // Закрываем файл
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
QString ChannelModel::driver() const
{
   return m_driver;
}

void ChannelModel::setDriver(const QString &n)
{
   m_driver = n;
   emit driverChanged(m_driver);
}
//---------------------------------------------------------------------------------------------
int ChannelModel::numarea() const
{
   return m_numarea;
}

void ChannelModel::setNumarea(const int &n)
{
   m_numarea = n;
   emit numareaChanged(m_numarea);
}
//---------------------------------------------------------------------------------------------
qreal ChannelModel::pagesize() const
{
   return m_pagesize;
}

void ChannelModel::setPagesize(const qreal &n)
{
   m_pagesize = n;
   emit pagesizeChanged(m_pagesize);
}
//---------------------------------------------------------------------------------------------
qreal ChannelModel::pageval() const
{
   return m_pageval;
}

void ChannelModel::setPageval(const qreal &n)
{
   m_pageval = n;
   emit pagevalChanged(m_pageval);
}
//---------------------------------------------------------------------------------------------
QVector<int> ChannelModel::deep() const
{
   return m_Deep;
}
QVector<int> ChannelModel::time() const
{
   return m_Time;
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
   m_Time.append(data[0]);
   m_Deep.append(data[1]);
   // сохраняем текущие показания прибора
   m_DataUE = data.mid(2);
   //QMessageBox::information(0, "Information", QString("%1").arg(m_DataUE[0]));
   //   for(int i=0;i<m_DeepTime.size();i++)
   //   {
   //      str_data += QString(" %1").arg(m_DeepTime[i].x());
   //   }
   //   QMessageBox::information(0, "Information", str_data);

   for(int i=0;i<m_numch;i++)
   {
      //Добавить преобразование к знаковому и беззнаковому
      str_data += QString("var k%1 = %2;\n").arg(i+1).arg(m_DataUE[i]);
   }
   //QMessageBox::information(0, "Information", str_data);

   QListIterator<ChElement*> it_data(m_data);
   while (it_data.hasNext())
   {
      it_data.next()->appendData(str_data,m_Deep.size()-1);
   }
   //if(m_data.size()==4) QMessageBox::information(0, "Information", QString("%1").arg(m_data[3]->dataCh().at(m_Deep.size()-1)));
   emit dataueChanged();
}

void ChannelModel::update(QAbstractSeries *series)
{
   if (series) {
      QXYSeries *xySeries = static_cast<QXYSeries *>(series);
      //        m_index++;
      //        if (m_index > m_data.count() - 1)
      //            m_index = 0;

      //        QVector<QPointF> points = m_data.at(m_index);
      // Use replace instead of clear + append, it's optimized for performance
      //        xySeries->replace(points);

   }
}
