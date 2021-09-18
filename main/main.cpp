#include <QAndroidService>

#include <QAndroidIntent>
#include <QQmlApplicationEngine>
#include <QQmlContext>


//#include <QRemoteObjectNode>
//#include <QTimer>
//#include <QUrl>
//#include "rep_qtandroidservice_replica.h"

#include "communication/servicecommunicator.h"

#include "controllers/mastercontroller.h"
#include "controllers/revenuecontroller.h"
#include "controllers/settingcontroller.h"

#if defined (Q_OS_ANDROID)
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include <QtSvg>
const QVector<QString> permissions({"android.permission.RECEIVE_SMS",
                                   "android.permission.FOREGROUND_SERVICE",
                                   "android.permission.INTERNET",
                                   "android.permission.GET_TASKS"});
#endif

void startService()
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                        "org/qtproject/example/qtandroidservice/QtAndroidService");
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
        "startService",
        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        serviceIntent.handle().object());
}

int main(int argc, char *argv[])
{
    qDebug()<<"argc :"<<argc;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

#if defined (Q_OS_ANDROID)
    //Request requiered permissions at runtime
    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return 0;
        }
    }
#endif

    //Register
    qmlRegisterType<MasterController>("SRC", 1, 0, "MasterController");
    qmlRegisterType<SettingController>("SRC", 1, 0,"SettingController");
    qmlRegisterType<RevenueController>("SRC", 1, 0,"RevenueController");

    qmlRegisterType<Transaction>("SRC", 1, 0,"Transaction");
    qmlRegisterType<TabAction>("SRC", 1, 0,"TabAction");
    qmlRegisterType<PropertyAction>("SRC", 1, 0,"PropertyAction");




    QQmlApplicationEngine engine;
    MasterController *masterController = new MasterController(&app);
    startService();

    engine.addImportPath("qrc:/");

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<QtAndroidServiceReplica> rep(repNode.acquire<QtAndroidServiceReplica>());
    engine.rootContext()->setContextProperty("qtAndroidService", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);
    rep->sendToService("Check for connecting remost");

    QObject::connect(rep.data(), &QtAndroidServiceReplica::messageFromService, [](const QString &message){
        qDebug() << "Service sent: " << message;
        //waitingMessage = message;
    });

    QObject::connect(masterController, &MasterController::sendMessage,[rep](const QString &msg){
        rep->sendToService(msg);
    });

    engine.rootContext()->setContextProperty(QLatin1String("masterController"), masterController);

    const QUrl url(QStringLiteral("qrc:/views/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
