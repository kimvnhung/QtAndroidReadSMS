#include "transaction.h"

Transaction::Transaction(QObject *parent, QString phone,
                         QString code, int value, QString time):
    QObject(parent)
{
    this->m_phone = phone;
    this->m_code = code;
    this->m_value = value;
    this->m_time = time;
}

Transaction::Transaction(QObject *parent, int id, QString phone,
                         QString code, int value, QString time, QString updateTime, bool status):
    Transaction(parent,phone,code,value,time)
{
    this->m_id = id;
    this->m_updateTime = updateTime;
    this->m_status = status;
}

Transaction::~Transaction()
{

}

void Transaction::setId(int id)
{
    this->m_id = id;
    emit idChanged();
}
void Transaction::setPhone(QString phone)
{
    this->m_phone = phone;
    emit phoneChanged();
}
void Transaction::setCode(QString code)
{
    this->m_code = code;
    emit codeChanged();
}
void Transaction::setValue(int value)
{
    this->m_value = value;
    emit valueChanged();
}

void Transaction::setTime(QString time)
{
    this->m_time = time;
    emit timeChanged();
}
void Transaction::setUpdateTime(QString updateTime)
{
    this->m_updateTime = updateTime;
    emit updateTimeChanged();
}


void Transaction::setStatus(bool isUpdated)
{
    this->m_status = isUpdated;
    emit statusChanged();
}
