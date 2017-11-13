#include "areadraw.h"

AreaDraw::AreaDraw(QObject *parent) : QObject(parent)
{

}
qreal AreaDraw::width() const
{
   return m_width;
}
void AreaDraw::setWidth(qreal width)
{
   if (m_width == width) {
       return;
   }

   m_width = width;

   emit widthChanged(m_width);
}

QString AreaDraw::name() const
{
   return m_name;
}
void AreaDraw::setName(QString name)
{
   if (m_name == name) {
       return;
   }

   m_name = name;

   emit nameChanged(m_name);
}

qreal AreaDraw::begin() const
{
   return m_begin;
}
void AreaDraw::setBegin(qreal begin)
{
   if (m_begin == begin) {
       return;
   }

   m_begin = begin;

   emit beginChanged(m_begin);
}

bool  AreaDraw::isOpened() const
{
   return m_isOpened;
}
void AreaDraw::setIsOpened(bool isOpened)
{
   if (m_isOpened == isOpened) {
      return;
   }

   m_isOpened = isOpened;

   emit isOpenedChanged(m_isOpened);
}

void AreaDraw::saveXML( QXmlStreamWriter &xmlWriter)
{
   xmlWriter.writeStartElement("name");//name
   xmlWriter.writeCharacters(property("name").toString());
   xmlWriter.writeEndElement();        //name

   xmlWriter.writeStartElement("width");//width
   xmlWriter.writeCharacters(property("width").toString());
   xmlWriter.writeEndElement();        //width

   xmlWriter.writeStartElement("begin");//begin
   xmlWriter.writeCharacters(property("begin").toString());
   xmlWriter.writeEndElement();        //begin
}
void AreaDraw::parseXML( QXmlStreamReader &xml)
{
   xml.readNext();
   while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "drawarea"))
   {
      if (xml.tokenType() == QXmlStreamReader::StartElement)
      {
         if(xml.name()=="name")
         {
            setProperty("name", xml.readElementText());
         }
         if(xml.name()=="width")
         {
            setProperty("width", xml.readElementText());
         }
         if(xml.name()=="begin")
         {
            setProperty("begin", xml.readElementText());
         }
      }
      xml.readNext();
   }
}
