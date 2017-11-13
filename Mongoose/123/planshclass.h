#ifndef PLANSHCLASS_H
#define PLANSHCLASS_H

#include <QObject>

class PlanshClass : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString name  READ name      WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(int countArea READ countArea WRITE setCountArea)
public:
   explicit PlanshClass(QObject *parent = nullptr);

   QString name() const;

   int countArea() const;
   void setCountArea(int);

private:
   QString m_name;
   int m_countArea;
signals:
   void nameSignal();
   void nameChanged(QString name);
public slots:
   void setName(const QString &);
};

#endif // PLANSHCLASS_H
