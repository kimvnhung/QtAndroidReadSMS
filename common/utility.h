#ifndef UTILITY_H
#define UTILITY_H

#include "constants.h"
#include "QtAndroid"

class Utility
{
public:
    static void showToast(const QString &message, int duration = Constants::ToastDuration::LONG);
    static QString getFullDigits(int number, int digitNumber);
    static int numberDigit(int number);
    static QString getDisplayValue(int number);
    static bool isNetworkConnected();
    static QString runCommand(QString command);
};

#endif // UTILITY_H
