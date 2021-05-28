#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlResult>
#include <QVariant>
#include <QList>

#include "model/transaction.h"

#include "comunication/jnimessenger.h"
#include "comunication/qtandroidservice.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr,QString databasePath = "");
    static DatabaseHandler *instance(){return m_instance;}

    QList<Transaction*> getTransactionList();
    static const QString DATABASE_NAME ;

    static const QString TABLE_NAME_AGENCY ;
    static const QString COLUMN_ID ;
    static const QString COLUMN_PHONE ;
    static const QString COLUMN_TRANSACTION_CODE ;
    static const QString COLUMN_VALUE ;
    static const QString COLUMN_TIME ;
    static const QString COLUMN_UPDATE_TIME ;
    static const QString COLUMN_STATUS ;

private:
    static DatabaseHandler* m_instance;


    QSqlDatabase db;
    //methods
    void log(QString content);

};

#endif // DATABASEREADER_H
