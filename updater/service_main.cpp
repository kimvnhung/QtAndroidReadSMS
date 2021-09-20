
#include <QDebug>
#include <QAndroidService>
#include "log.h"
#include "qtandroidservice.h"
#include <QUrl>
#include <QRemoteObjectHost>
#include "appcommunication.h"


int main(int argc, char *argv[])
{
    qWarning() << "Service starting with BroadcastReceiver from separate .so file";

    QAndroidService app(argc, argv);

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    AppCommunication appCommunication;
    srcNode.enableRemoting(&appCommunication);
    LOGD(__FUNCTION__+__LINE__);
    LOGD("Hello World!");


    return app.exec();
}
