#include "qtandroidservice.h"

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QtDebug>

QtAndroidService *QtAndroidService::m_instance = nullptr;
const QString QtAndroidService::LOG_KEY = "log";

static void receivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    emit QtAndroidService::instance()->messageFromService(
        env->GetStringUTFChars(value, nullptr));
}

QtAndroidService::QtAndroidService(QObject *parent) : QObject(parent)
{
    m_instance = this;

    registerNatives();
    registerBroadcastReceiver();

    connect(this, &QtAndroidService::messageFromService, this, &QtAndroidService::receiveMessage);
}

void QtAndroidService::receiveMessage(const QString &message)
{
    if(message == "REFRESH_DATA"){

    }
}

void QtAndroidService::sendToService(const QString &name)
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                "com/hungkv/autolikeapp/comunication/QtAndroidService");
    serviceIntent.putExtra("name", name.toUtf8());
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

void QtAndroidService::registerNatives()
{
    JNINativeMethod methods[] {
        {"sendToQt", "(Ljava/lang/String;)V", reinterpret_cast<void *>(receivedFromAndroidService)}};
    QAndroidJniObject javaClass("com/hungkv/autolikeapp/comunication/ActivityUtils");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void QtAndroidService::registerBroadcastReceiver()
{
    QAndroidJniEnvironment env;
    jclass javaClass = env.findClass("com/hungkv/autolikeapp/comunication/ActivityUtils");
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
}
