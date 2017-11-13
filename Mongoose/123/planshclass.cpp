#include "planshclass.h"

PlanshClass::PlanshClass(QObject *parent) : QObject(parent)
{
   m_name = "Mongoose";
   m_countArea = 3;
}

QString PlanshClass::name() const
{
   return m_name;
}

void PlanshClass::setName(const QString &n)
{
   m_name = n;
   emit nameChanged(m_name);
}

int PlanshClass::countArea() const
{
   return m_countArea;
}

void PlanshClass::setCountArea(int s)
{
   m_countArea = s;
}
