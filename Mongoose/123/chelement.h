#ifndef CHELEMENT_H
#define CHELEMENT_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>

class ChElement : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString color     READ color    WRITE setColor    NOTIFY colorChanged)
   Q_PROPERTY(QString text      READ text     WRITE setText     NOTIFY textChanged)
   Q_PROPERTY(QString name      READ name     WRITE setName     NOTIFY nameChanged)
   Q_PROPERTY(QString unit      READ unit     WRITE setUnit     NOTIFY unitChanged)
   Q_PROPERTY(QString convert   READ convert  WRITE setConvert  NOTIFY convertChanged)
   Q_PROPERTY(qreal   diva      READ diva     WRITE setDiva     NOTIFY divaChanged)
   Q_PROPERTY(qreal   begpoint  READ begpoint WRITE setBegpoint NOTIFY begpointChanged)
   Q_PROPERTY(qreal   wrpoint   READ wrpoint  WRITE setWrpoint  NOTIFY wrpointChanged)
   Q_PROPERTY(int     area      READ area     WRITE setArea     NOTIFY areaChanged)
   Q_PROPERTY(int     chanell   READ chanell  WRITE setChanell  NOTIFY chanellChanged)
   Q_PROPERTY(int     decpl     READ decpl    WRITE setDecpl    NOTIFY decplChanged)
public:
   explicit ChElement(QObject *parent = 0);

   QString color() const;
   void setColor(QString color);

   QString text() const;
   void setText(QString text);

   QString name() const;
   void setName(QString name);

   QString unit() const;
   void setUnit(QString unit);

   QString convert() const;
   void setConvert(QString convert);

   qreal diva() const;
   void setDiva(qreal diva);

   qreal begpoint() const;
   void setBegpoint(qreal begpoint);

   qreal wrpoint() const;
   void setWrpoint(qreal wrpoint);

   int  area() const;
   void setArea(int area);

   int  chanell() const;
   void setChanell(int area);

   int  decpl() const;
   void setDecpl(int decpl);

signals:
   void colorChanged(QString color);
   void textChanged(QString text);
   void nameChanged(QString name);
   void unitChanged(QString unit);
   void convertChanged(QString convert);
   void divaChanged(qreal diva);
   void begpointChanged(qreal begpoint);
   void wrpointChanged(qreal wrpoint);
   void areaChanged(int area);
   void chanellChanged(int chanell);
   void decplChanged(int decpl);
public slots:
   void appendData(QString &data);
private:
   QString m_color;        //цвет кривой
   QString m_text;         //название кривой
   QString m_name;         //имя кривой
   QString m_unit;         //еденица измерения
   QString m_convert;      //javascript код преобразования у.е.
   qreal   m_diva;         //цена деления
   qreal   m_begpoint;     //Начало отсчета
   qreal   m_wrpoint;      //Точка записи
   int     m_decpl;        //Цифр после запятой
   int     m_area;         //Номер области вывода
   int     m_chanell;      //Номер канала
   QVector<qreal> m_data; //массив с данными занчение канала

   QScriptEngine ScrEngine;
   QScriptValue  ScrValue;
};

#endif // CHELEMENT_H
