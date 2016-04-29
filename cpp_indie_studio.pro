TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lOgreMain -lOIS -lboost_system

SOURCES += sources/main.cpp \
    sources/gui.cpp \
    sources/ogretext.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    includes/gui.h \
    includes/ogretext.h

INCLUDEPATH += includes

DISTFILES += \
    Makefile
