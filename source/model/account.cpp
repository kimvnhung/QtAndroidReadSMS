#include "account.h"

Account::Account(QObject *parent,QString username,QString password,QString name) : QObject(parent)
{
    this->mUsername = username;
    this->mPassword = password;
    this->mName = name;
}

QString Account::name(){
    return this->mName;
}
