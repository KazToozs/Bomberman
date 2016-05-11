TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -O3 -ffast-math -lX11 -lXcursor -L./lib/irrlicht/bin -lIrrlicht

SOURCES += sources/main.cpp \
    sources/Gui/ControlEventReceiver.cpp \
    sources/Gui/Gui.cpp \
    sources/Map/Map.cpp \
    sources/Player/src/Bomb.cpp \
    sources/Player/src/Game.cpp \
    sources/Player/src/Keybind.cpp \
    sources/Player/src/Player.cpp \
    sources/Player/src/PowerBomb.cpp \
    sources/Player/src/PowerRange.cpp \
    sources/Player/src/PowerSpeed.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    includes/Gui.hh \
    includes/ControlEventReceiver.hh \
    includes/Case.h \
    includes/Map.hh \
    includes/Bomb.hh \
    includes/Game.hh \
    includes/IPlayer.hh \
    includes/IPowerup.hh \
    includes/Keybind.hh \
    includes/Player.hh \
    includes/PowerBomb.hh \
    includes/PowerRange.hh \
    includes/PowerSpeed.hh

INCLUDEPATH += includes ./lib/irrlicht/include

DISTFILES += \
    Makefile
