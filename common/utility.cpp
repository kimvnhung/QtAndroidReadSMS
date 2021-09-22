#include "utility.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcess>
#include "log.h"

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

QString Utility::getDisplayValue(int number)
{
    if(number==0){
        return "0";
    }
    QString rt = "";
    int para = number;
    while (para/1000 > 0){
        rt = (para < number?(Utility::getFullDigits(para%1000,3)+","):Utility::getFullDigits(para%1000,3))+rt;
        para /= 1000;
    }
    if(para != 0){
        rt = QString::number(para)+ "," + rt;
    }
    return rt;
}

bool Utility::isNetworkConnected(int timeout){

    QString pingResult = runCommand("ping -c 1 google.com",timeout);
    if (pingResult.contains("ping: unknown host www.google.com")){
        return false;
    }
    QStringList lines = pingResult.split("\n");

    for(QString line : lines){
        if (line.startsWith("rtt min/avg/max/mdev")){
            QString speedInfor = line.replace("rtt min/avg/max/mdev = ","");

            QStringList speeds = speedInfor.split("/");
            QString min = speeds.at(0);
            min = min.replace(".","");

            if (min.toInt() > 50000){
                return true;
            }
        }
    }
    return false;
}

QString Utility::runCommand(QString command,int timeout){
    QProcess process;
    process.start(command);
    process.waitForFinished(timeout);
    return process.readAll().data();
}

QList<Transaction*> Utility::fromJson(QString json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if(!doc.isEmpty()
            && doc.isArray()){
        QJsonArray jsonArr = doc.array();
        QList<Transaction*> result = QList<Transaction*>();
        for(int i=0;i<jsonArr.size();i++){
            result.append(Transaction::fromJson(QJsonDocument(jsonArr.at(i).toObject()).toJson(QJsonDocument::Compact)));
        }
        return result;
    }

    return QList<Transaction*>();
}

QString Utility::toJsonArray(QList<Transaction *> list)
{
    QJsonArray jsonArr;
    for(int i=0;i<list.size();i++){
        jsonArr.append(QJsonDocument::fromJson(list.at(i)->toJson().toUtf8()).object());
    }
    if(jsonArr.size() > 0){
        return QJsonDocument(jsonArr).toJson(QJsonDocument::Compact);
    }
    return "[]";
}
