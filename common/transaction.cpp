#include "transaction.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "utility.h"


QString Transaction::format = "dd-MM-yyyy  hh:mm:ss";

Transaction::Transaction(QObject *parent, QString phone,
                         QString code, int value, QString time,QString smsContent):
    QObject(parent),
    m_phone(phone),
    m_code(code),
    m_value(value),
    m_smsContent(smsContent)
{
    this->m_time = QDateTime::fromString(time,format);
}

Transaction::Transaction(QObject *parent, int id, QString phone, QString code,
                         int value, QString time, QString updateTime, int status, QString smsContent):
    Transaction(parent,phone,code,value,time,smsContent)
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
        int id = doc[Constants::TransactionField::ID].toInt();
        QString phone = doc[Constants::TransactionField::PHONE].toString();
        QString code = doc[Constants::TransactionField::CODE].toString();
        int value = doc[Constants::TransactionField::VALUE].toInt();
        QString time  = doc[Constants::TransactionField::TIME].toString();
        QString update_time = doc[Constants::TransactionField::UPDATE_TIME].toString();
        int status = doc[Constants::TransactionField::STATUS].toInt();
        QString smsContent = doc[Constants::TransactionField::SMS_CONTENT].toString();
        return new Transaction(nullptr,id,phone,code,value,time,update_time,status,smsContent);
    }

    return nullptr;
}

QString Transaction::toJson()
{
    QJsonObject obj;
    obj.insert(Constants::TransactionField::ID,this->getId());
    obj.insert(Constants::TransactionField::PHONE,this->getPhone());
    obj.insert(Constants::TransactionField::CODE, this->getCode());
    obj.insert(Constants::TransactionField::VALUE, this->getValue());
    obj.insert(Constants::TransactionField::TIME, this->getTime());
    obj.insert(Constants::TransactionField::UPDATE_TIME, this->getUpdateTime());
    obj.insert(Constants::TransactionField::STATUS, this->getStatus());
    obj.insert(Constants::TransactionField::SMS_CONTENT, this->getSmsContent());
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

void Transaction::setSmsContent(QString smsContent)
{
    this->m_smsContent = smsContent;
}
