#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T18:59:07
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Json_MQ_Socket
TEMPLATE = lib

DEFINES += MQ_JSON_COMMUNICATOR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        MQ_Json_Communicator.cpp \
    Socket_Json_Communicator.cpp \
    IJson_Communicator.cpp

HEADERS += \
        MQ_Json_Communicator.h \
    IJson_Communicator.h \
    Socket_Json_Communicator.h

LIBS += -L$$PWD/../qamqp/build/Debug/src/ -lqamqp
INCLUDEPATH += $$PWD/../qamqp/src
DEPENDPATH += $$PWD/../qamqp/build/Debug/src
unix {
    target.path = /usr/lib
    INSTALLS += target
}
