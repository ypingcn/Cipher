#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T20:33:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cipher
TEMPLATE = app

CONFIG += c++11

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
        main.cpp \
        widget.cpp \
    caesarcipher.cpp \
    playfaircipher.cpp \
    hillcipher.cpp \
    matrix.cpp

HEADERS += \
        widget.h \
    caesarcipher.h \
    playfaircipher.h \
    hillcipher.h \
    matrix.h

FORMS += \
        widget.ui

RESOURCES += \
    resource/resource.qrc

RC_FILE += resource/main.rc

icons.files = resource/cipher.png
desktop.files = cipher.desktop
i18n.files = i18n/*.qm

TRANSLATIONS += i18n/zh-cn.ts

isEmpty(INSTALL_PREFIX) {
    unix: INSTALL_PREFIX = /usr
    else: INSTALL_PREFIX = ..
}

unix: {
    desktop.path = $$INSTALL_PREFIX/share/applications
    icons.path = $$INSTALL_PREFIX/share/icons/hicolor/128x128/apps
    i18n.path = $$INSTALL_PREFIX/bin/cipher/i18n
    INSTALLS += desktop icons i18n
}

target.files = cipher
target.path = $$INSTALL_PREFIX/bin/cipher

INSTALLS += target
