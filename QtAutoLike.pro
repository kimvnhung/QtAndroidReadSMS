QT += qml quick androidextras sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

INCLUDEPATH += source/

SOURCES += \
        source/comunication/jnimessenger.cpp \
        source/comunication/qtandroidservice.cpp \
        source/comunication/utility.cpp \
        source/controllers/mastercontroller.cpp \
        source/controllers/revenuecontroller.cpp \
        source/database/databasehandler.cpp \
        main.cpp \
        source/model/account.cpp \
        source/model/tabaction.cpp \
        source/model/transaction.cpp

HEADERS += \
        source/comunication/constants.h \
        source/comunication/jnimessenger.h \
        source/comunication/qtandroidservice.h \
        source/comunication/utility.h \
        source/controllers/mastercontroller.h \
        source/controllers/revenuecontroller.h \
        source/database/databasehandler.h \
        source/model/account.h \
        source/model/tabaction.h \
        source/model/transaction.h

RESOURCES += views.qrc \
    components.qrc \
    values.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android{
    DISTFILES += \
        source/android/res/drawable/ic_launcher.png \
        source/android/src/com/hungkv/autolikeapp/MainActivity.java \
        source/android/src/com/hungkv/autolikeapp/Constants.java \
        source/android/src/com/hungkv/autolikeapp/comunication/JniMessenger.java \
        source/android/src/com/hungkv/autolikeapp/comunication/QtAndroidService.java \
        source/android/src/com/hungkv/autolikeapp/database/DatabaseHandler.java \
        source/android/src/com/hungkv/autolikeapp/database/Transaction.java \
        source/android/AndroidManifest.xml \
        source/android/src/com/hungkv/autolikeapp/listener/SmsReceiver.java

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/source/android

    deployment.files += AutoLikeAgency.db
    deployment.path = /assets
    INSTALLS += deployment
}

DISTFILES +=




