#include "chelement.h"
#include <QVector>

ChElement::ChElement(QObject *parent) :QObject(parent)
{
   //m_data = new QVector<QPointF>;
}
// преобразовываем полученные данные в реальные единицы
void ChElement::appendData(QString &data)
{
   ScrValue = ScrEngine.evaluate(data + "\n" + m_convert);
   if(!ScrValue.isError())
   {
      m_data.append(ScrValue.toNumber());
   }
   else
   {
      //ошибка
   }
}
//-----------------------------------------------
QString ChElement::color() const
{
    return m_color;
}

void ChElement::setColor(QString color)
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

    emit chanellChanged(m_decpl);
}
//-----------------------------------------------
