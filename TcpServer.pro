#-------------------------------------------------
#
# Project created by QtCreator 2022-08-26T18:20:45
#
#-------------------------------------------------

QT       += serialport
QT       += core gui network
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = logo3.ico

TARGET = TcpServer
TEMPLATE = app


SOURCES += main.cpp\
        admin.cpp \
        form.cpp \
        menu.cpp \
        oop.cpp \
        picture.cpp \
        register.cpp \
        ser.cpp \
        tt.cpp


HEADERS  += \
    admin.h \
    form.h \
    menu.h \
    oop.h \
    picture.h \
    register.h \
    ser.h \
    tt.h


FORMS    += \
    admin.ui \
    form.ui \
    menu.ui \
    oop.ui \
    picture.ui \
    register.ui \
    ser.ui \
    tt.ui


RESOURCES += \
    ../img/pic.qrc \
    sour.qrc
