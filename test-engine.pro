TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += test/main.cpp

unix:!macx: LIBS += -L$$PWD/bin/ -lNobel-Engine

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

unix:!macx: LIBS += -L$$PWD/../Nobel-Base/bin/ -lNobel-Base

INCLUDEPATH += $$PWD/../Nobel-Base/src
DEPENDPATH += $$PWD/../Nobel-Base/src

unix:!macx: LIBS += -lGL

unix:!macx: LIBS += -lglfw

unix:!macx: LIBS += -lGLEW

unix|win32: LIBS += -lGLU
