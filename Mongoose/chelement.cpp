#include "chelement.h"
#include <QVector>
#include <QMessageBox>

ChElement::ChElement(QObject *parent) :QObject(parent)
{
   //m_data = new QVector<QPointF>;
   m_data.reserve(32);
   m_data.append(0);
}
// преобразовываем полученные данные в реальные единицы
void ChElement::appendData(QString &data, int size)
{
   ScrValue = ScrEngine.evaluate(data + "\n" + m_convert);
   if(m_data.size() < size) m_data.resize(size);
   if(!ScrValue.isError())
   {
      m_curval = ScrValue.toNumber();
      m_data.append(m_curval);
      emit curvalChanged(m_curval);
   }
   else
   {
      m_data.append(0);
      emit curvalChanged(m_curval);
      //ошибка
      //QMessageBox::information(0, "Information", QString("%1").arg(data + "\n" + m_convert));
   }
}
//-----------------------------------------------
QColor ChElement::color() const
{
   return m_color;
}

void ChElement::setColor(QColor color)
{
   if (m_color == color) {
      return;
   }

   m_color = color;

   emit colorChanged(m_color);
}
//-----------------------------------------------
QString ChElement::text() const
{
   return m_text;
}

void ChElement::setText(QString text)
{
   if (m_text == text) {
      return;
   }

   m_text = text;

   emit textChanged(m_text);
}
//-----------------------------------------------
QString ChElement::name() const
{
   return m_name;
}
void ChElement::setName(QString name)
{
   if (m_name == name) {
      return;
   }

   m_name = name;

   emit nameChanged(m_name);
}
//-----------------------------------------------
QString ChElement::unit() const
{
   return m_unit;
}
void ChElement::setUnit(QString unit)
{
   if (m_unit == unit) {
      return;
   }

   m_unit = unit;

   emit unitChanged(m_unit);
}
//-----------------------------------------------
QString ChElement::convert() const
{
   return m_convert;
}
void ChElement::setConvert(QString convert)
{
   if (m_convert == convert) {
      return;
   }

   m_convert = convert;

   emit nameChanged(m_convert);
}
//-----------------------------------------------
qreal ChElement::diva() const
{
   return m_diva;
}
void ChElement::setDiva(qreal diva)
{
   if (m_diva == diva) {
      return;
   }

   m_diva = diva;

   emit divaChanged(m_diva);
}
//-----------------------------------------------
qreal ChElement::begpoint() const
{
   return m_begpoint;
}
void ChElement::setBegpoint(qreal begpoint)
{
   if (m_begpoint == begpoint) {
      return;
   }

   m_begpoint = begpoint;

   emit begpointChanged(m_begpoint);
}
//-----------------------------------------------
qreal ChElement::wrpoint() const
{
   return m_wrpoint;
}
void ChElement::setWrpoint(qreal wrpoint)
{
   if (m_wrpoint == wrpoint) {
      return;
   }

   m_wrpoint = wrpoint;

   emit wrpointChanged(m_wrpoint);
}
//-----------------------------------------------
qreal ChElement::subval() const
{
   return m_subval;
}
void ChElement::setSubval(qreal subval)
{
   if (m_subval == subval) {
      return;
   }

   m_subval = subval;

   emit subvalChanged(m_subval);
}
//-----------------------------------------------
int  ChElement::area() const
{
   return m_area;
}
void ChElement::setArea(int area)
{
   if (m_area == area) {
      return;
   }

   m_area = area;

   emit areaChanged(m_area);
}
//-----------------------------------------------
int  ChElement::chanell() const
{
   return m_chanell;
}
void ChElement::setChanell(int chanell)
{
   if (m_chanell == chanell) {
      return;
   }

   m_chanell = chanell;

   emit chanellChanged(m_chanell);
}
//-----------------------------------------------
int  ChElement::decpl() const
{
   return m_decpl;
}
//-----------------------------------------------
void ChElement::setDecpl(int decpl)
{
   if (m_decpl == decpl) {
      return;
   }

   m_decpl = decpl;

   emit decplChanged(m_decpl);
}
//-----------------------------------------------
int  ChElement::areaindex() const
{
   return m_index;
}
//-----------------------------------------------
void ChElement::setAreaindex(int index)
{
   if (m_index == index) {
      return;
   }

   m_index = index;

   emit areaindexChanged(m_index);
}
//-----------------------------------------------
qreal  ChElement::curval() const
{
   return m_curval;
}
//-----------------------------------------------
QVector<qreal> ChElement::dataCh() const
{
   return m_data;
}
//-----------------------------------------------
void ChElement::SetData(int index)
{
   m_data.resize(index);
}
//-----------------------------------------------
bool  ChElement::isOpened() const
{
   return m_isOpened;
}
void ChElement::setIsOpened(bool isOpened)
{
   if (m_isOpened == isOpened) {
      return;
   }

   m_isOpened = isOpened;

   emit isOpenedChanged(m_isOpened);
}
//-----------------------------------------------
void ChElement::saveXML( QXmlStreamWriter &xmlWriter)
{
   xmlWriter.writeStartElement("name");//name
   xmlWriter.writeCharacters(property("name").toString());
   xmlWriter.writeEndElement();        //name

   xmlWriter.writeStartElement("color");//color
   xmlWriter.writeCharacters(property("color").toString());
   xmlWriter.writeEndElement();        //color

   xmlWriter.writeStartElement("text");//text
   xmlWriter.writeCharacters(property("text").toString());
   xmlWriter.writeEndElement();        //text

   xmlWriter.writeStartElement("unit");//unit
   xmlWriter.writeCharacters(property("unit").toString());
   xmlWriter.writeEndElement();        //unit

   xmlWriter.writeStartElement("convert");//convert
   xmlWriter.writeCharacters(property("convert").toString());
   xmlWriter.writeEndElement();        //convert

   xmlWriter.writeStartElement("diva");//diva
   xmlWriter.writeCharacters(property("diva").toString());
   xmlWriter.writeEndElement();        //diva

   xmlWriter.writeStartElement("begpoint");//begpoint
   xmlWriter.writeCharacters(property("begpoint").toString());
   xmlWriter.writeEndElement();        //begpoint

   xmlWriter.writeStartElement("wrpoint");//wrpoint
   xmlWriter.writeCharacters(property("wrpoint").toString());
   xmlWriter.writeEndElement();        //wrpoint

   xmlWriter.writeStartElement("curval");//curval
   xmlWriter.writeCharacters(property("curval").toString());
   xmlWriter.writeEndElement();        //curval

   xmlWriter.writeStartElement("area");//area
   xmlWriter.writeCharacters(property("area").toString());
   xmlWriter.writeEndElement();        //area

   xmlWriter.writeStartElement("chanell");//chanell
   xmlWriter.writeCharacters(property("chanell").toString());
   xmlWriter.writeEndElement();        //chanell

   xmlWriter.writeStartElement("decpl");//decpl
   xmlWriter.writeCharacters(property("decpl").toString());
   xmlWriter.writeEndElement();        //decpl
}
void ChElement::parseXML( QXmlStreamReader &xml)
{
   xml.readNext();
   while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "chelement"))
   {
      if (xml.tokenType() == QXmlStreamReader::StartElement)
      {
         if(xml.name()=="name")
         {
            setProperty("name", xml.readElementText());
         }
         if(xml.name()=="color")
         {
            setProperty("color", xml.readElementText());
         }
         if(xml.name()=="text")
         {
            setProperty("text", xml.readElementText());
         }
         if(xml.name()=="unit")
         {
            setProperty("unit", xml.readElementText());
         }
         if(xml.name()=="convert")
         {
            setProperty("convert", xml.readElementText());
         }
         if(xml.name()=="diva")
         {
            setProperty("diva", xml.readElementText());
         }
         if(xml.name()=="begpoint")
         {
            setProperty("begpoint", xml.readElementText());
         }
         if(xml.name()=="wrpoint")
         {
            setProperty("wrpoint", xml.readElementText());
         }
         if(xml.name()=="decpl")
         {
            setProperty("decpl", xml.readElementText());
         }
         if(xml.name()=="area")
         {
            setProperty("area", xml.readElementText());
         }
      }
      xml.readNext();
   }
}
