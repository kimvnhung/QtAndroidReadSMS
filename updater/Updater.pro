TEMPLATE = lib
TARGET = updater
CONFIG += dll
QT += core androidextras xml network remoteobjects

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#LIBS += -L$$PWD/libs/armeabi-v7a -lchilkatAndroid
#INCLUDEPATH += $$PWD/include
#DEPENDPATH += $PWD/include

REPC_SOURCE += ../common/qtandroidservice.rep
INCLUDEPATH += ../common

SOURCES += \
    service_main.cpp \
    webapirequest.cpp \
    qtandroidservice.cpp

HEADERS += \
    webapirequest.h \
    constants.h \
    qtandroidservice.h

include($$PWD/android_openssl/openssl.pri)
