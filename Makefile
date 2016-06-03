NAME        =	cpp_indie_game

SRC         =	sources/main.cpp	\
		sources/Gui/Gui.cpp	\
		sources/Gui/ControlEventReceiver.cpp \
		sources/Player/src/PowerBomb.cpp \
		sources/Player/src/PowerRange.cpp \
		sources/Player/src/PowerSpeed.cpp \
		sources/Player/src/Game.cpp \
		sources/Player/src/Player.cpp \
		sources/Player/src/Keybind.cpp \
		sources/Player/src/Bomb.cpp \
		sources/Menu/ConfirmButton.cpp \
		sources/Menu/ContinueButton.cpp \
		sources/Menu/ExitButton.cpp \
		sources/Menu/IAButton.cpp \
		sources/Menu/Menu.cpp \
		sources/Menu/OptionButton.cpp \
		sources/Menu/PlayerButton.cpp \
		sources/Map/Map.cpp 		\
		sources/Menu/BackButton.cpp	\
		sources/AI/src/AI.cpp

LUA		= ./lib/lua/liblua53.so

SFML	= ./lib/SFML/lib/libsfml-system.so
SFML	+= ./lib/SFML/lib/libsfml-audio.so

OBJ         =	$(SRC:.cpp=.o)

INCLUDEPATH +=  -I./includes -I/usr/X11R6/include -I./lib/irrlicht/include -I./includes/LuaBridge -I./lib/SFML/include

CPPFLAGS    =	$(INCLUDEPATH) -O3 -ffast-math -std=c++11 -g3

CPP         =	g++

LIBS        =	-lX11 -lXcursor -lpthread -Llib/bin/ -lIrrlicht $(SFML) $(LUA)

all:		$(NAME)

$(NAME)	    :	$(OBJ)
		$(CPP) $(OBJ) -o $(NAME) $(LIBS)

clean       :
		rm -f $(OBJ)

fclean      :	clean
		rm -f $(NAME)

re          :	fclean all


