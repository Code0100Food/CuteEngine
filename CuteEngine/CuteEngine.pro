#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:16:11
#
#-------------------------------------------------

QT       += core gui
QT	+= opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += "PRIMITIVE_SIZE=\"10.0\""

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -lopengl32
LIBS += -opengl32
RESOURCES += \
    icons.qrc

SOURCES += \ 
    Components/component.cpp \
    Components/transform.cpp \
    Engine/hierarchywidget.cpp \
    Engine/input.cpp \
    Engine/inspector.cpp \
    Engine/mainscene.cpp \
    Engine/mainwindow.cpp \
    Engine/myopenglwidget.cpp \
    Engine/qt_application.cpp \
    basicprimitive.cpp \
    entity.cpp \
    main.cpp \
    viewport.cpp

HEADERS += \
    Components/component.h \
    Components/transform.h \
    Engine/hierarchywidget.h \
    Engine/input.h \
    Engine/inspector.h \
    Engine/mainscene.h \
    Engine/mainwindow.h \
    Engine/myopenglwidget.h \
    Engine/qt_application.h \
    basicprimitive.h \
    entity.h \
    viewport.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    standard_fragment.frag \
    standard_vertex.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/Assimp/include
INCLUDEPATH += $$PWD/Engine
INCLUDEPATH += $$PWD/Components
DEPENDPATH += $$PWD/Assimp/include
DEPENDPATH += $$PWD/Engine
DEPENDPATH += $$PWD/Components
