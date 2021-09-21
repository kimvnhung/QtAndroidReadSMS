#include "transaction.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

QString Transaction::format = "dd-MM-yyyy  hh:mm:ss";

Transaction::Transaction(QObject *parent, QString phone,
                         QString code, int value, QString time):
    QObject(parent)
{
    this->m_phone = phone;
    this->m_code = code;
    this->m_value = value;
    this->m_time = QDateTime::fromString(time,format);
}

Transaction::Transaction(QObject *parent, int id, QString phone,
                         QString code, int value, QString time, QString updateTime, int status):
    Transaction(parent,phone,code,value,time)
{
    this->m_id = id;
    this->m_updateTime = QDateTime::fromString(updateTime,format);
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
    this->m_time = QDateTime::fromString(time,format);
    emit timeChanged();
}

void Transaction::set_Time(QDateTime time)
{
    this->m_time = time;
    emit timeChanged();
}

void Transaction::set_UpdateTime(QDateTime updateTime)
{
    this->m_updateTime = updateTime;
    emit updateTimeChanged();
}

void Transaction::setUpdateTime(QString updateTime)
{
    this->m_updateTime = QDateTime::fromString(updateTime,format);;
    emit updateTimeChanged();
}


void Transaction::setStatus(int status)
{
    this->m_status = status;
    emit statusChanged();
}

QString Transaction::getDisplayValue()
{
    return Utility::getDisplayValue(m_value);
}

Transaction* Transaction::fromJson(QString json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if(!doc.isEmpty()
            && doc.isObject()){
        int id = doc[Constants::Transaction::ID].toInt();
        QString phone = doc[Constants::Transaction::PHONE].toString();
        QString code = doc[Constants::Transaction::CODE].toString();
        int value = doc[Constants::Transaction::VALUE].toInt();
        QString time  = doc[Constants::Transaction::TIME].toString();
        QString update_time = doc[Constants::Transaction::UPDATE_TIME].toString();
        int status = doc[Constants::Transaction::STATUS].toInt();
        return new Transaction(nullptr,id,phone,code,value,time,update_time,status);
    }

    return nullptr;
}

QString Transaction::toJson()
{
    QJsonObject obj;
    obj.insert(Constants::Transaction::ID,this->getId());
    obj.insert(Constants::Transaction::PHONE,this->getPhone());
    obj.insert(Constants::Transaction::CODE, this->getCode());
    obj.insert(Constants::Transaction::VALUE, this->getValue());
    obj.insert(Constants::Transaction::TIME, this->getTime());
    obj.insert(Constants::Transaction::UPDATE_TIME, this->getUpdateTime());
    obj.insert(Constants::Transaction::STATUS, this->getStatus());
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}
