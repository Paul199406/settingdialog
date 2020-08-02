#-------------------------------------------------
#
# Project created by QtCreator 2020-08-01T10:45:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SettingDialog
TEMPLATE = app


SOURCES += main.cpp\
        settingdialog.cpp \
    settingtitlebar.cpp \
    basewidget.cpp \
    test.cpp

HEADERS  += settingdialog.h \
    settingtitlebar.h \
    basewidget.h \
    test.h

FORMS    += settingdialog.ui \
    test.ui

DISTFILES += \
    Resources/SettingTitleBar.css

RESOURCES += \
    settingdialog.qrc
