#include "databasehandler.h"

#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

DatabaseHandler* DatabaseHandler::m_instance = nullptr;

const QString DatabaseHandler::DATABASE_NAME = "AutoLikeAgency.db";
const QString DatabaseHandler::TABLE_NAME_AGENCY = "Agency";
const QString DatabaseHandler::COLUMN_ID = "_id";
const QString DatabaseHandler::COLUMN_PHONE = "_phone";
const QString DatabaseHandler::COLUMN_TRANSACTION_CODE = "_transaction_code";
const QString DatabaseHandler::COLUMN_VALUE = "_value";
const QString DatabaseHandler::COLUMN_TIME = "_time";
const QString DatabaseHandler::COLUMN_UPDATE_TIME = "_update_time";
const QString DatabaseHandler::COLUMN_STATUS = "_status";

DatabaseHandler::DatabaseHandler(QObject *parent, QString databasePath) : QObject(parent)
{

    m_instance = this;

    db = QSqlDatabase::addDatabase("QSQLITE","MyConnection");
    db.setConnectOptions("QSQLITE_OPEN_READONLY");
    db.setDatabaseName(databasePath);
    //db.database("MyConnection",true);

    if(db.isValid()){
        log("Database Valid");
    }
    log("Test log");
    QFile dfile("assets:/databases/"+DATABASE_NAME);
    if (dfile.exists())
    {
         log("Database Existed");
    }
    if(!db.open()){
        log("Database Open Fail");
    }
}

//public
QList<Transaction*> DatabaseHandler::getTransactionList()
{
    QList<Transaction*> rt = QList<Transaction*>();
    if(db.isOpen()){
        //debug
        QSqlQuery query2(db);
        query2.prepare("SELECT name FROM sqlite_master WHERE type='table'");
        if(query2.exec()){
            log("Query2 exec true");
        }
        while (query2.next()) {
            log("Table : "+query2.value(0).toString());
        }
        //


        QSqlQuery query = db.exec(QString("select * from "+TABLE_NAME_AGENCY));
        while (query.next()) {
            int id = query.value(COLUMN_ID).toInt();
            QString phone  = query.value(COLUMN_PHONE).toString();
            QString code = query.value(COLUMN_TRANSACTION_CODE).toString();
            int value = query.value(COLUMN_VALUE).toInt();
            QString time = query.value(COLUMN_TIME).toString();
            QString updateTime = query.value(COLUMN_UPDATE_TIME).toString();
            int status = query.value(COLUMN_STATUS).toInt();
            Transaction* item = new Transaction(this,id,phone,code,value,time,updateTime,status);
            rt.append(item);
        }
        log("rtsize : "+QString::number(rt.size()));
    }else {
        log("Database open fail2");
    }

    return rt;
}

QList<Transaction*> DatabaseHandler::getTransactionListByDate(QDate date)
{
    QList<Transaction*> rt = QList<Transaction*>();
    if(db.isOpen()){
        //debug
        QSqlQuery query2(db);
        query2.prepare("SELECT name FROM sqlite_master WHERE type='table'");
        if(query2.exec()){
            log("Query2 exec true");
        }
        while (query2.next()) {
            log("Table : "+query2.value(0).toString());
        }
        //


        QSqlQuery query = db.exec(QString("select * from "+TABLE_NAME_AGENCY));
        while (query.next()) {
            int id = query.value(COLUMN_ID).toInt();
            QString phone  = query.value(COLUMN_PHONE).toString();
            QString code = query.value(COLUMN_TRANSACTION_CODE).toString();
            int value = query.value(COLUMN_VALUE).toInt();
            QString time = query.value(COLUMN_TIME).toString();
            QString updateTime = query.value(COLUMN_UPDATE_TIME).toString();
            int status = query.value(COLUMN_STATUS).toInt();
            Transaction* item = new Transaction(this,id,phone,code,value,time,updateTime,status);
            if(item->get_Time().date().day() == date.day()){
                rt.append(item);
            }
        }
        log("rtsize : "+QString::number(rt.size()));
    }else {
        log("Database open fail2");
    }

    return rt;
}

void DatabaseHandler::update(Transaction *transaction)
{
    //call to java for writing data
    QJsonObject obj;
    obj.insert(Constants::Transaction::ID,transaction->getId());
    obj.insert(Constants::Transaction::PHONE,transaction->getPhone());
    obj.insert(Constants::Transaction::CODE, transaction->getCode());
    obj.insert(Constants::Transaction::VALUE, transaction->getValue());
    obj.insert(Constants::Transaction::TIME, transaction->getTime());
    obj.insert(Constants::Transaction::UPDATE_TIME, transaction->getUpdateTime());
    obj.insert(Constants::Transaction::STATUS, transaction->getStatus());
    QtAndroidService::instance()->updateTransaction(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

//private
void DatabaseHandler::log(QString content)
{
    QtAndroidService::instance()->log(content);
}
