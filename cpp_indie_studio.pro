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
    sources/Map/main.cpp

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
    includes/LuaBridge/detail/CFunctions.h \
    includes/LuaBridge/detail/ClassInfo.h \
    includes/LuaBridge/detail/Constructor.h \
    includes/LuaBridge/detail/dump.h \
    includes/LuaBridge/detail/FuncTraits.h \
    includes/LuaBridge/detail/Iterator.h \
    includes/LuaBridge/detail/LuaException.h \
    includes/LuaBridge/detail/LuaHelpers.h \
    includes/LuaBridge/detail/LuaRef.h \
    includes/LuaBridge/detail/Namespace.h \
    includes/LuaBridge/detail/Stack.h \
    includes/LuaBridge/detail/TypeList.h \
    includes/LuaBridge/detail/TypeTraits.h \
    includes/LuaBridge/detail/Userdata.h

INCLUDEPATH += includes ./lib/irrlicht/include

DISTFILES += \
    Makefile \
    includes/LuaBridge/detail/Stack.h~
