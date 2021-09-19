#include "qtandroidservice.h"

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonDocument>


QtAndroidService *QtAndroidService::m_instance = nullptr;
QList<QString> QtAndroidService::inbox = QList<QString>();
QString QtAndroidService::DatabasePath = "";

static void receivedAndTransferToUI(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QtAndroidService::inbox.append(env->GetStringUTFChars(value,nullptr));

}

static void receivedAndPerform(JNIEnv *env, jobject thiz, jstring value)
{
    LOGD("Perform");
    if(QtAndroidService::instance()->jniObject() == nullptr){
        jobject globObj = env->NewGlobalRef(thiz);
        QtAndroidService::instance()->passingObject(globObj);
    }
    QtAndroidService::instance()->handleServiceMessage(env->GetStringUTFChars(value,nullptr));
}

QtAndroidService::QtAndroidService(QObject *parent) :
    QtAndroidServiceSource(parent)
{
    m_instance = this;

    registerNative();

    if(inbox.size() > 0){
        inbox.clear();
    }

    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, &QTimer::timeout, this, &QtAndroidService::handleAsynTask);
    timer->start();

//    delayForUpdate = new QTimer(this);
//    delayForUpdate->setInterval(1000);
//    delayForUpdate->setSingleShot(true);
//    connect(delayForUpdate, &QTimer::timeout,[]{
//       inbox.append(Constants::Info::UPDATE_DATA_INFO);
//    });

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
    QAndroidIntent serviceIntent(Constants::Action::UPDATE_TRANSACTION_STATUS_ACTION);

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(m_javaServiceInstance->object());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                m_javaServiceInstance->object(),
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

void QtAndroidService::handleAsynTask()
{
    if(!inbox.isEmpty()){
        emit messageFromService(inbox.first());
        inbox.removeFirst();
    }

    webAPI->postAsync();
//    delayForUpdate->start();
}

void QtAndroidService::handleServiceMessage(const QString &message)
{
    LOGD("handleServiceMess : %s",message.toUtf8().data());
    if(message == Constants::Action::UPDATE_TO_SERVER){
        LOGD("onUpdateToServer");
        if(DatabasePath.size() > 0){
            databaseHandler = new DatabaseHandler(sender(),DatabasePath);
            DatabasePath = "";
        }
        if(databaseHandler != nullptr
                || DatabaseHandler::instance() != nullptr){
            if(databaseHandler == nullptr){
                databaseHandler = DatabaseHandler::instance();
            }
            QList<Transaction*> listTrans = databaseHandler->getTransactionList(sender());
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

    if(message.startsWith(Constants::Info::DATABASE_DECLARE_INFO)){
        if(DatabaseHandler::instance() == nullptr){
            DatabasePath = message.mid(Constants::Info::DATABASE_DECLARE_INFO.length());
        }
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
            if(databaseHandler != nullptr){
//                QJsonObject obj;
//                obj.insert(Constants::Transaction::ID,0);
//                obj.insert(Constants::Transaction::PHONE,phone);
//                obj.insert(Constants::Transaction::CODE, code);
//                obj.insert(Constants::Transaction::VALUE, value);
//                obj.insert(Constants::Transaction::TIME, "");
//                obj.insert(Constants::Transaction::UPDATE_TIME, "");
//                obj.insert(Constants::Transaction::STATUS, Transaction::ACCEPTED);
//                updateTransaction(QJsonDocument(obj).toJson(QJsonDocument::Compact));
                Transaction trans;
                trans.setCode(code);
                trans.setPhone(phone);
                trans.setValue(value);
                trans.setStatus(Transaction::ACCEPTED);
                databaseHandler->update(&trans);
            }
        }else {
            QJsonDocument body = QJsonDocument::fromJson(webAPI->getAsynBody().toUtf8());
            if(!body.isEmpty()
                    && body.isObject()
                    && databaseHandler != nullptr){
                QString code = body["code"].toString();
                int money = body["money"].toInt();
                Transaction trans;
                trans.setCode(code);
                trans.setValue(money);
                trans.setStatus(Transaction::REJECT);
//                QJsonObject obj;
//                obj.insert(Constants::Transaction::ID,0);
//                obj.insert(Constants::Transaction::PHONE,"");
//                obj.insert(Constants::Transaction::CODE, code);
//                obj.insert(Constants::Transaction::VALUE, money);
//                obj.insert(Constants::Transaction::TIME, "");
//                obj.insert(Constants::Transaction::UPDATE_TIME, "");
//                obj.insert(Constants::Transaction::STATUS, Transaction::REJECT);
//                updateTransaction(QJsonDocument(obj).toJson(QJsonDocument::Compact));
                databaseHandler->update(&trans);
            }
        }
    }
}

void QtAndroidService::transferDatabasePath(QString path)
{
    LOGD("");
    databaseHandler = new DatabaseHandler(this,path);
}
