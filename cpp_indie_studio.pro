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
    sources/Player/src/PowerSpeed.cpp \
    sources/Menu/ConfirmButton.cpp \
    sources/Menu/ContinueButton.cpp \
    sources/Menu/ExitButton.cpp \
    sources/Menu/IAButton.cpp \
    sources/Menu/Menu.cpp \
    sources/Menu/OptionButton.cpp \
    sources/Menu/PlayerButton.cpp \
    sources/AI/src/AI.cpp \
    sources/AI/test/main.cpp \
    sources/Map/main.cpp \
    sources/Menu/BackButton.cpp

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
    includes/PowerSpeed.hh \
    includes/AI.hh \
    includes/ConfirmButton.hh \
    includes/ContinueButton.hh \
    includes/ExitButton.hh \
    includes/IAButton.hh \
    includes/IButtons.hh \
    includes/Menu.hh \
    includes/OptionButton.hh \
    includes/PlayerButton.hh \

INCLUDEPATH += includes ./lib/irrlicht/include ./include/LuaBridge/detail ./lib/SFML/include

DISTFILES += \
    Makefile \
