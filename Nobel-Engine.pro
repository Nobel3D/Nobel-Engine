#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T17:13:11
#
#-------------------------------------------------

QT       -= core gui

TARGET = Nobel-Engine
TEMPLATE = lib

DEFINES += NOBELENGINE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Data/Point.cpp \
    src/Data/Shader.cpp \
    src/Data/VideoMode.cpp \
    src/Graphics/Draw.cpp \
    src/Graphics/Form.cpp \
    src/Graphics/Text.cpp \
    src/Object/Triangles.cpp \
    src/Data/Color.cpp \
    src/Graphics/Camera.cpp

HEADERS +=\
    src/Data/OpenGL.h \
    src/Data/Point.h \
    src/Data/Shader.h \
    src/Data/VideoMode.h \
    src/Graphics/Draw.h \
    src/Graphics/Form.h \
    src/Graphics/Text.h \
    src/Object/Triangles.h \
    src/nedef.h \
    src/NobelEngine.h \
    src/Data/Color.h \
    src/Graphics/Camera.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../Nobel-Base/bin/ -lNobel-Base

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/../Nobel-Base/src
DEPENDPATH += $$PWD/../Nobel-Base/src
