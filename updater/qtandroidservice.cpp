#include "qtandroidservice.h"

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QDebug>

QtAndroidService *QtAndroidService::m_instance = nullptr;

static void receivedAndTransferToUI(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    LOGD("Transfer");
   QtAndroidService::instance()->sendToService(env->GetStringUTFChars(value, nullptr));
}

static void receivedAndPerform(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    LOGD("Perform");
}

QtAndroidService::QtAndroidService(QObject *parent) :
    QtAndroidServiceSource(parent)
{
    m_instance = this;

    registerNative();
}

void QtAndroidService::registerNative()
{
    JNINativeMethod methods[] {
        {"emitToUI", "(Ljava/lang/String;)V", reinterpret_cast<void *>(receivedAndTransferToUI)},
        {"emitToBackground", "(Ljava/lang/String;)V", reinterpret_cast<void *>(receivedAndPerform)}
    };
    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void QtAndroidService::startBackgroundService()
{
    QAndroidIntent serviceIntent(Constants::Action::START_BACKGROUND_SERVICE_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidActivity().object(),
                objectClass);

    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

void QtAndroidService::startForegroundService()
{
    QAndroidIntent serviceIntent(Constants::Action::START_FOREGROUND_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidActivity().object(),
                objectClass);

    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

void QtAndroidService::updateTransaction(QString jsonTrans)
{
    QAndroidIntent serviceIntent(Constants::Action::UPDATE_TRANSACTION_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidActivity().object(),
                objectClass);
    serviceIntent.putExtra("Transaction", jsonTrans.toUtf8());

    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

void QtAndroidService::log(const QString &message)
{
    QAndroidIntent serviceIntent(Constants::Action::LOG_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidActivity().object(),
                objectClass);
    serviceIntent.putExtra("message", message.toUtf8());

    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

