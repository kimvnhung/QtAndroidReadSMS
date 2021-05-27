#include "databasehandler.h"

#include "comunication/qtandroidservice.h"

#include <QFile>

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

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{
    connect(this, &DatabaseHandler::log, QtAndroidService::instance(), &QtAndroidService::sendToService);

    db = QSqlDatabase::addDatabase("QSQLITE","MyConnection");
    db.setDatabaseName(DATABASE_NAME);

    if(db.isValid()){
        emit log("Database Valid");
    }
    emit log("Test log");
    QFile dfile(":/"+DATABASE_NAME);
    if (dfile.exists())
    {
         emit log("Database Existed");
    }
    if(!db.open()){
        emit log("Database Open Fail");
    }
}

DatabaseHandler* DatabaseHandler::instance()
{
    if(m_instance == nullptr){
        m_instance = new DatabaseHandler();
    }

    return m_instance;
}

//public
QList<Transaction*> DatabaseHandler::getTransactionList()
{
    QList<Transaction*> rt = QList<Transaction*>();
    if(db.isOpen()){
        //debug
        QSqlQuery query2 = db.exec("SELECT name FROM sqlite_master WHERE type='table'");
        while (query2.next()) {
            emit log("Table : "+query2.value(0).toString());
        }
        //


        QSqlQuery query = db.exec(QString("select * from "+TABLE_NAME_AGENCY));
        QSqlRecord record = query.record();
        while (query.next()) {
            int id = query.value(COLUMN_ID).toInt();
            QString phone  = query.value(COLUMN_PHONE).toString();
            QString code = query.value(COLUMN_TRANSACTION_CODE).toString();
            int value = query.value(COLUMN_VALUE).toInt();
            QString time = query.value(COLUMN_TIME).toString();
            QString updateTime = query.value(COLUMN_UPDATE_TIME).toString();
            bool status = query.value(COLUMN_STATUS).toInt() == 1;
            Transaction* item = new Transaction(this,id,phone,code,value,time,updateTime,status);
            rt.append(item);
        }
        emit log("rtsize : "+QString::number(rt.size()));
    }else {
        emit log("Database open fail2");
    }

    return rt;
}
