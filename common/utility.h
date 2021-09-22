#ifndef UTILITY_H
#define UTILITY_H

#include "constants.h"
#include "QtAndroid"
#include "transaction.h"

class Utility
{
public:
    static void showToast(const QString &message, int duration = Constants::ToastDuration::LONG);
    static QString getFullDigits(int number, int digitNumber);
    static int numberDigit(int number);
    static QString getDisplayValue(int number);
    static bool isNetworkConnected(int timeout = 10000);
    static QString runCommand(QString command,int timeout = 10000);
    static QString toJsonArray(QList<Transaction*> list);
    static QList<Transaction*> fromJson(QString json);
    static QByteArray encodeTransactionPackge(QList<Transaction*> list);
    static QList<Transaction*> decodeTransactionPackage(QByteArray data);
};

#endif // UTILITY_H
