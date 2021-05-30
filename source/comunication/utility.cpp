#include "utility.h"

void Utility::showToast(const QString &message, int duration){
    // all the magic must happen on Android UI thread
    QtAndroid::runOnAndroidThread([message, duration] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(message);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(duration));
        toast.callMethod<void>("show");
    });
}

QString Utility::getFullDigits(int number, int digitNumber)
{
    int numDigit = numberDigit(number);
    if(numDigit >= digitNumber){
        return QString::number(number);
    }

    QString rt = QString::number(number);
    for(int i=0;i<(digitNumber-numDigit);i++){
        if(number == 0
                && i==0){
            continue;
        }
        rt = "0"+rt;
    }
    return rt;
}

int Utility::numberDigit(int number)
{
    int count = 0;
    while (number > 0) {
        count++;
        number /= 10;
    }
    return count;
}
