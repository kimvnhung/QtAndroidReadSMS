#include "qtandroidservice.h"

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonDocument>


QtAndroidService *QtAndroidService::m_instance = nullptr;

static void receivedActionAndData(JNIEnv *env, jobject thiz, jstring action,jstring data)
{
    LOGD("");
    if(QtAndroidService::instance()->jniObject() == nullptr){
        jobject globObj = env->NewGlobalRef(thiz);
        QtAndroidService::instance()->passingObject(globObj);
    }
    QtAndroidService::instance()->handleActionWithData(env->GetStringUTFChars(action,nullptr),env->GetStringUTFChars(data,nullptr));
}

static void receivedAction(JNIEnv *env, jobject thiz, jstring action)
{
    LOGD("Perform");
    if(QtAndroidService::instance()->jniObject() == nullptr){
        jobject globObj = env->NewGlobalRef(thiz);
        QtAndroidService::instance()->passingObject(globObj);
    }
    QtAndroidService::instance()->handleAction(env->GetStringUTFChars(action,nullptr));
}

QtAndroidService::QtAndroidService(QObject *parent) :
    QObject(parent)
{
    m_instance = this;

    registerNative();

    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, &QTimer::timeout, this, &QtAndroidService::handleAsynTask);
    timer->start();

    needToUpdate = QList<QString>();

    webAPI = new WebAPIRequest(this);
    connect(webAPI, &WebAPIRequest::networkResponsed,this, &QtAndroidService::onNetworkResponse);
}

QtAndroidService::~QtAndroidService()
{
    if(timer != nullptr){
        if(timer->isActive()){
            timer->stop();
        }
        delete timer;
    }

    if(delayForUpdate != nullptr){
        if(delayForUpdate->isActive()){
            delayForUpdate->stop();
        }
        delete delayForUpdate;
    }
}

void QtAndroidService::registerNative()
{
    JNINativeMethod methods[] {
        {"emitToBackground", "(Ljava/lang/String;)V", reinterpret_cast<void *>(receivedAction)},
        {"emitToBackground", "(Ljava/lang/String;Ljava/lang/String;)V", reinterpret_cast<void *>(receivedActionAndData)}
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

QtAndroidService* QtAndroidService::instance()
{
    QMutex mutex;
    mutex.lock();
    if(m_instance == nullptr) {
        m_instance = new QtAndroidService();
    }
    mutex.unlock();
    return m_instance;
}

void QtAndroidService::updateTransaction(QString jsonTrans)
{
    QAndroidIntent serviceIntent(Constants::Action::UPDATE_TRANSACTION_STATUS_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidContext().object(),
                objectClass);
    serviceIntent.putExtra("Transaction", jsonTrans.toUtf8());

    QAndroidJniObject result = QtAndroid::androidContext().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
//    QAndroidJniObject service("com/hungkv/autolikeapp/communication/QtAndroidService");
//    m_javaServiceInstance->callObjectMethod(
//                "updateTransactionStatus",
//                "(Ljava/lang/String;)V",
//                QAndroidJniObject::fromString(jsonTrans).object());

}

void QtAndroidService::updateTransactionStatus()
{
    for(int i=0;i<needToUpdate.size();i++){
        updateTransaction(needToUpdate.first());
        needToUpdate.removeFirst();
        i--;
    }
    //when finish posting
//    if(webAPI->getAsynBody() == ""){
//        updateInfo();
//    }
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

void QtAndroidService::handleAsynTask()
{
    webAPI->postAsync();
    //while finish post
    if(webAPI->getAsynBody() == ""){
        updateTransactionStatus();
    }
}

void QtAndroidService::handleAction(const QString &action)
{
    LOGD("Action : %s",action.toUtf8().data());
    if(action == Constants::Action::UPDATE_TO_SERVER){
        LOGD("onUpdateToServer");
        if(!Utility::isNetworkConnected()){
            LOGD("Network is not available!");
            return;
        }
        if(DatabaseHandler::instance() != nullptr){
            QList<Transaction*> listTrans = DatabaseHandler::instance()->getTransactionList();
            for(int i=0;i<listTrans.size();i++){
                if(listTrans.at(i)->getStatus() != Transaction::PENDING){
                    listTrans.removeAt(i);
                    i--;
                }
            }
            updateToServer(listTrans);
            pushOnGoogleSheet(listTrans);
        }else {
            LOGD("Database null");
        }
    }
}

void QtAndroidService::handleActionWithData(const QString &action, const QString &data)
{
    if(action == Constants::Info::DATABASE_DECLARE_INFO){
        if(DatabaseHandler::instance() == nullptr){
            DatabaseHandler *database = new DatabaseHandler(nullptr,data);
            Q_UNUSED(database)
            LOGD("Database Size : %d",DatabaseHandler::instance()->getTransactionList().size());

            Transaction *trans = DatabaseHandler::instance()->getTransactionList().first();
            trans->setStatus(Transaction::ACCEPTED);
            QJsonObject obj;
            obj.insert(Constants::Transaction::ID,trans->getId());
            obj.insert(Constants::Transaction::PHONE,trans->getPhone());
            obj.insert(Constants::Transaction::CODE, trans->getCode());
            obj.insert(Constants::Transaction::VALUE, trans->getValue());
            obj.insert(Constants::Transaction::TIME, trans->getTime());
            obj.insert(Constants::Transaction::UPDATE_TIME, trans->getUpdateTime());
            obj.insert(Constants::Transaction::STATUS, Transaction::ACCEPTED);

            updateTransaction(QJsonDocument(obj).toJson(QJsonDocument::Compact));
        }
    }
}

void QtAndroidService::onInternetConnectionChanged(bool isConnected)
{
    if(isConnected){
        handleAction(Constants::Action::UPDATE_TO_SERVER);
    }
}

void QtAndroidService::passingObject(QAndroidJniObject javaObject)
{
    {
        LOGD("");
        if(javaObject == nullptr) {
            delete m_javaServiceInstance;
            m_javaServiceInstance = nullptr;
        } else {
            if(m_javaServiceInstance == nullptr) {
                m_javaServiceInstance = new QAndroidJniObject(javaObject);
                if(m_javaServiceInstance->isValid()) {
                    LOGD("Valid jni");
                } else {
                   m_javaServiceInstance = nullptr;
                }
            }
        }
    }
}

void QtAndroidService::updateToServer(QList<Transaction*> listTrans)
{
    for(int i=0;i<listTrans.size();i++){
        Transaction* para = listTrans.at(i);
        QJsonObject update;
        update.insert("code",para->getCode());
        update.insert("money",para->getValue());
        webAPI->addPostRequest(QJsonDocument(update).toJson(QJsonDocument::Compact));
    }
}

void QtAndroidService::pushOnGoogleSheet(QList<Transaction*> listTrans)
{

}

void QtAndroidService::onNetworkResponse(QString response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    if(!doc.isNull()
            && doc.isObject()){
        QJsonObject res = doc.object();
        if(res["message"].toString() == "Success"){
            QString phone = res["data"].toObject()["username"].toString();
            QString code = res["data"].toObject()["code"].toString();
            int value = res["data"].toObject()["value"].toInt();
            if(DatabaseHandler::instance() != nullptr){
                QJsonObject obj;
                obj.insert(Constants::Transaction::ID,0);
                obj.insert(Constants::Transaction::PHONE,phone);
                obj.insert(Constants::Transaction::CODE, code);
                obj.insert(Constants::Transaction::VALUE, value);
                obj.insert(Constants::Transaction::TIME, "");
                obj.insert(Constants::Transaction::UPDATE_TIME, "");
                obj.insert(Constants::Transaction::STATUS, Transaction::ACCEPTED);
                needToUpdate.append(QJsonDocument(obj).toJson(QJsonDocument::Compact));
//                Transaction trans;
//                trans.setCode(code);
//                trans.setPhone(phone);
//                trans.setValue(value);
//                trans.setStatus(Transaction::ACCEPTED);
//                databaseHandler->update(&trans);
            }
        }else {
            QJsonDocument body = QJsonDocument::fromJson(webAPI->getAsynBody().toUtf8());
            if(!body.isEmpty()
                    && body.isObject()
                    && DatabaseHandler::instance() != nullptr){
                QString code = body["code"].toString();
                int money = body["money"].toInt();
//                Transaction trans;
//                trans.setCode(code);
//                trans.setValue(money);
//                trans.setStatus(Transaction::REJECT);
                QJsonObject obj;
                obj.insert(Constants::Transaction::ID,0);
                obj.insert(Constants::Transaction::PHONE,"");
                obj.insert(Constants::Transaction::CODE, code);
                obj.insert(Constants::Transaction::VALUE, money);
                obj.insert(Constants::Transaction::TIME, "");
                obj.insert(Constants::Transaction::UPDATE_TIME, "");
                obj.insert(Constants::Transaction::STATUS, Transaction::REJECT);
                needToUpdate.append(QJsonDocument(obj).toJson(QJsonDocument::Compact));
//                databaseHandler->update(&trans);
            }
        }
    }
}

void QtAndroidService::updateInfo()
{
    QAndroidIntent serviceIntent(Constants::Info::UPDATE_DATA_INFO);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidContext().object(),
                objectClass);

    QAndroidJniObject result = QtAndroid::androidContext().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

