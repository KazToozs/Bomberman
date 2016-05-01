TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -O3 -ffast-math -lX11 -lXcursor -L./lib/irrlicht/bin -lIrrlicht

SOURCES += sources/main.cpp \
    sources/gui.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    includes/gui.h

INCLUDEPATH += includes ./lib/irrlicht/include

DISTFILES += \
    Makefile
