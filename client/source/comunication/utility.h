#ifndef UTILITY_H
#define UTILITY_H

#include "references.h"
#include "QtAndroid"

class Utility
{
public:
    static void showToast(const QString &message, ToastDuration duration = LONG);

};

#endif // UTILITY_H
