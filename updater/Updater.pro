TEMPLATE = lib
TARGET = updater
CONFIG += dll
QT += core androidextras sql svg xml network remoteobjects

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

REPC_SOURCE += ../common/qtandroidservice.rep
INCLUDEPATH += ../common

SOURCES += \
    service_main.cpp \
    webapirequest.cpp \
    qtandroidservice.cpp \
    databasehandler.cpp \
    transaction.cpp \
    utility.cpp

HEADERS += \
    webapirequest.h \
    constants.h \
    qtandroidservice.h \
    databasehandler.h \
    transaction.h \
    utility.h

include($$PWD/android_openssl/openssl.pri)
