TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -O3 -ffast-math -lX11 -lXcursor -L./lib/irrlicht/bin -lIrrlicht

SOURCES += sources/main.cpp \
    sources/Gui/ControlEventReceiver.cpp \
    sources/Gui/Gui.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    includes/Gui.hh \
    includes/ControlEventReceiver.hh

INCLUDEPATH += includes ./lib/irrlicht/include

DISTFILES += \
    Makefile
