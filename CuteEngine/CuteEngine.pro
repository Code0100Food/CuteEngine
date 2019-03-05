#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:16:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += opengl

LIBS += -lopengl32

RESOURCES += \
    icons.qrc

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    inspector.cpp \
    myopenglwidget.cpp \
    hierarchywidget.cpp \
    mainscene.cpp \
    qt_application.cpp \
    circlewidget.cpp \
    entity.cpp \
    basicprimitive.cpp \
    component.cpp

HEADERS += \
        mainwindow.h \
    inspector.h \
    myopenglwidget.h \
    hierarchywidget.h \
    mainscene.h \
    qt_application.h \
    circlewidget.h \
    entity.h \
    basicprimitive.h \
    component.h

FORMS += \
        mainwindow.ui \
    rendering.ui \
    inspector.ui
