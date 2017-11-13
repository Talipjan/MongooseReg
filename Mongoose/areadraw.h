#ifndef AREADRAW_H
#define AREADRAW_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QObject>
#include <QString>
#include <QVariant>

class AreaDraw : public QObject
{
   Q_OBJECT
   Q_PROPERTY(qreal   width      READ width      WRITE setWidth      NOTIFY widthChanged)
   Q_PROPERTY(qreal   begin      READ begin      WRITE setBegin      NOTIFY beginChanged)
   Q_PROPERTY(QString name       READ name       WRITE setName       NOTIFY nameChanged)
   Q_PROPERTY(bool    isOpened   READ isOpened   WRITE setIsOpened   NOTIFY isOpenedChanged)
public:
   explicit AreaDraw(QObject *parent = 0);

   qreal width() const;
   void setWidth(qreal width);

   qreal begin() const;
   void setBegin(qreal begin);

   QString name() const;
   void setName(QString name);

   bool isOpened() const;
signals:
   void widthChanged(qreal   width);
   void beginChanged(qreal   begin);
   void nameChanged(QString name);
   void isOpenedChanged(bool isOpened);
public slots:
   void saveXML( QXmlStreamWriter &xml);
   void parseXML( QXmlStreamReader &xml);
   void setIsOpened(bool isOpened);
private:
   qreal   m_width;
   qreal   m_begin;
   QString m_name;
   bool    m_isOpened;
};

#endif // AREADRAW_H
