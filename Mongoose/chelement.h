#ifndef CHELEMENT_H
#define CHELEMENT_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QColor>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class ChElement : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString name      READ name      WRITE setName      NOTIFY nameChanged)
   Q_PROPERTY(QColor color      READ color     WRITE setColor     NOTIFY colorChanged)
   Q_PROPERTY(QString text      READ text      WRITE setText      NOTIFY textChanged)
   Q_PROPERTY(QString unit      READ unit      WRITE setUnit      NOTIFY unitChanged)
   Q_PROPERTY(QString convert   READ convert   WRITE setConvert   NOTIFY convertChanged)
   Q_PROPERTY(qreal   diva      READ diva      WRITE setDiva      NOTIFY divaChanged)
   Q_PROPERTY(qreal   begpoint  READ begpoint  WRITE setBegpoint  NOTIFY begpointChanged)
   Q_PROPERTY(qreal   wrpoint   READ wrpoint   WRITE setWrpoint   NOTIFY wrpointChanged)
   Q_PROPERTY(qreal   curval    READ curval                       NOTIFY curvalChanged)
   Q_PROPERTY(int     area      READ area      WRITE setArea      NOTIFY areaChanged)
   Q_PROPERTY(int     chanell   READ chanell   WRITE setChanell   NOTIFY chanellChanged)
   Q_PROPERTY(int     decpl     READ decpl     WRITE setDecpl     NOTIFY decplChanged)
   Q_PROPERTY(int     areaindex READ areaindex WRITE setAreaindex NOTIFY areaindexChanged)
   Q_PROPERTY(bool    isOpened  READ isOpened  WRITE setIsOpened  NOTIFY isOpenedChanged)
   Q_PROPERTY(QVector<qreal>  dataCh     READ dataCh           )
public:
   explicit ChElement(QObject *parent = 0);

   QVector<qreal> dataCh() const;

   QColor color() const;
   void setColor(QColor color);

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

   int area() const;
   void setArea(int area);

   int  chanell() const;
   void setChanell(int area);

   int  decpl() const;
   void setDecpl(int decpl);

   bool isOpened() const;
   void setIsOpened(bool isOpened);

   int  areaindex() const;
   void setAreaindex(int areaindex);

   qreal curval() const;

   void SetData(int index);
signals:
   void colorChanged(QColor color);
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
   void areaindexChanged(int index);
   void curvalChanged(qreal curval);
   void isOpenedChanged(bool isOpened);
public slots:
   void appendData(QString &data, int size);
   void saveXML( QXmlStreamWriter &xmlWriter);
   void parseXML( QXmlStreamReader &xml);
private:
   QColor  m_color;        //цвет кривой
   QString m_text;         //название кривой
   QString m_name;         //имя кривой
   QString m_unit;         //еденица измерения
   QString m_convert;      //javascript код преобразования у.е.
   qreal   m_diva;         //цена деления
   qreal   m_begpoint;     //Начало отсчета
   qreal   m_wrpoint;      //Точка записи
   qreal   m_curval;       //Текущие показания
   int     m_decpl;        //Цифр после запятой
   int     m_area;         //Номер области вывода
   int     m_chanell;      //Номер канала
   int     m_index = 0;    //Индекс на дорожке
   bool    m_isOpened;
   QVector<qreal> m_data;  //массив с данными занчение канала

   QScriptEngine ScrEngine;
   QScriptValue  ScrValue;
};

#endif // CHELEMENT_H
