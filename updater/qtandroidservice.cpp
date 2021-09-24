#include "qtandroidservice.h"

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QDir>
#include "utility.h"


QtAndroidService *QtAndroidService::m_instance = nullptr;
QString QtAndroidService::checkedPath = QDir::currentPath()+"/checked.info";
int QtAndroidService::ASYNC_INTERVAL = 1000;

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
    LOGD("");
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

    LOGD("Timer start");
    timer = new QTimer(this);
    timer->setInterval(ASYNC_INTERVAL);
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

void QtAndroidService::updateTransaction(QString jsonTrans, QString action)
{
    QAndroidIntent serviceIntent(action);

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

}

void QtAndroidService::updateTransactionStatus()
{
    for(int i=0;i<needToUpdate.size();i++){
        if(i==0){
            qDebug()<<__FUNCTION__<<__LINE__;
        }
        updateTransaction(needToUpdate.first());
        needToUpdate.removeFirst();
        i--;

    }
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

    updateTransactionStatus();

    //counter for delete sms
    counterForDeleteSms++;
    if(counterForDeleteSms*ASYNC_INTERVAL >= 30*1000){
        counterForDeleteSms = 0;
        deleteSmsOverMonth();
    }
}

void QtAndroidService::handleAction(const QString &action)
{
    //LOGD("Action : %s",action.toUtf8().data());
    if(action == Constants::Action::UPDATE_TO_SERVER){
        LOGD("onUpdateToServer");
        if(!Utility::isNetworkConnected()){
            LOGD("Network is not available!");
            return;
        }
        if(DatabaseHandler::instance() != nullptr){
            QList<Transaction*> listTrans = DatabaseHandler::instance()->getTransactionList();
            for(int i=0;i<listTrans.size();i++){
                LOGD("id : %d - status : %d",listTrans.at(i)->getId(),listTrans.at(i)->getStatus());
                if(listTrans.at(i)->getStatus() != Transaction::PENDING){
                    listTrans.removeAt(i);
                    i--;
                }
            }
            LOGD("listTrans size : %d",listTrans.size());
            if(listTrans.size() == 0){
                return;
            }
            updateToServer(listTrans);
            pushOnGoogleSheet(listTrans);
        }else {
            LOGD("Database null");
        }
    }else if(action == Constants::Action::REVENUE_REQUEST_ACTION){
        if(DatabaseHandler::instance() != nullptr){
            QList<Transaction*> todayList = DatabaseHandler::instance()->getTransactionListByDate(QDate::currentDate());
            LOGD("todayList size : %d",todayList.size());
            emit requestUI(Constants::Action::REVENUE_REQUEST_ACTION,Utility::toJsonArray(todayList));
        }
    }else if(action == Constants::Action::HISTORY_REQUEST_ACTION){
        if(DatabaseHandler::instance() != nullptr){
            updateTransactionStatus();
            QList<Transaction*> dataList = DatabaseHandler::instance()->getTransactionList();
            LOGD("dataList size : %d",dataList.size());
            emit requestUI(Constants::Action::HISTORY_REQUEST_ACTION,Utility::toJsonArray(dataList));
        }
    }else if(action == Constants::Action::SERVICE_CLOCK_ACTION){
        //LOGD("");

    }else if(action == Constants::Action::REFRESH_UI_ACTION){
        if(DatabaseHandler::instance() != nullptr){
            emit requestUI(Constants::Action::REFRESH_UI_ACTION);
        }
    }
}

void QtAndroidService::handleActionWithData(const QString &action, const QString &data)
{
    if(action == Constants::Info::DATABASE_DECLARE_INFO){
        if(DatabaseHandler::instance() == nullptr){
            LOGD("Initialize database handler");
            DatabaseHandler *database = new DatabaseHandler(nullptr,data);
            Q_UNUSED(database)

            emit requestUI(Constants::Info::DATABASE_DECLARE_INFO);

        }
    }else if(action == Constants::Action::REPORTS_REQUEST_ACTION){
        if(DatabaseHandler::instance() != nullptr){
            QList<Transaction*> dataList = DatabaseHandler::instance()->getTransactionListByDate(QDate::fromString(data,"dd/MM/yy"));
            LOGD("dataList size : %d",dataList.size());
            emit requestUI(Constants::Action::REPORTS_REQUEST_ACTION,Utility::toJsonArray(dataList));
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
    qDebug()<<__FUNCTION__<<__LINE__;
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
    if(listTrans.size()>0){
        LOGD("Trans - id : %d, \nsms_content : %s",listTrans.at(0)->getId(),listTrans.at(0)->getSmsContent().toUtf8().data());
    }
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
            QString update_time = QDateTime::fromString(
                        res["data"].toObject()["updated_at"].toString(),
                        "yyyy-MM-ddTHH:mm:ss.zzzZ")
                    .toString(Transaction::format);
            if(DatabaseHandler::instance() != nullptr){
//                QJsonObject obj;
//                obj.insert(Constants::TransactionField::ID,0);
//                obj.insert(Constants::TransactionField::PHONE,phone);
//                obj.insert(Constants::TransactionField::CODE, code);
//                obj.insert(Constants::TransactionField::VALUE, value);
//                obj.insert(Constants::TransactionField::TIME, "");
//                obj.insert(Constants::TransactionField::UPDATE_TIME, update_time);
//                obj.insert(Constants::TransactionField::STATUS, Transaction::ACCEPTED);
//                obj.insert(Con)
                Transaction trans(nullptr,-1,phone,code,value,"",update_time,Transaction::ACCEPTED,"");
                needToUpdate.append(trans.toJson());
            }
        }else {
            QJsonDocument body = QJsonDocument::fromJson(webAPI->getAsynBody().toUtf8());
            if(!body.isEmpty()
                    && body.isObject()
                    && DatabaseHandler::instance() != nullptr){
                QString code = body["code"].toString();
                int money = body["money"].toInt();
                QString updateTime = QDateTime::currentDateTime().toString(Transaction::format);
                Transaction trans(nullptr,-1,"",code,money,"",updateTime,Transaction::REJECT,"");
                needToUpdate.append(trans.toJson());
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

void QtAndroidService::deleteSmsOverMonth()
{
    QAndroidIntent serviceIntent(Constants::Action::DELETE_SMS_ACTION);

    QAndroidJniObject javaClass("com/hungkv/autolikeapp/communication/QtAndroidService");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    serviceIntent.handle().callObjectMethod(
                "setClass",
                "(Landroid/content/Context;Ljava/lang/Class;)Landroid/content/Intent;",
                QtAndroid::androidContext().object(),
                objectClass);

    QString phoneList = "";
    if(DatabaseHandler::instance() != nullptr){
        foreach(Transaction *trans , DatabaseHandler::instance()->getTransactionList()){
            phoneList += trans->getPhone();
        }
    }

    serviceIntent.putExtra("Keys", phoneList.toUtf8());

    QAndroidJniObject result = QtAndroid::androidContext().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}
