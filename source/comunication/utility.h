#ifndef UTILITY_H
#define UTILITY_H

#include "references.h"
#include "QtAndroid"

class Utility
{
public:
    static void showToast(const QString &message, ToastDuration duration = LONG);
    static QString getFullDigits(int number, int digitNumber);
    static int numberDigit(int number);
};

#endif // UTILITY_H
