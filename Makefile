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
		sources/AI/src/AI.cpp


OBJ         =	$(SRC:.cpp=.o)

INCLUDEPATH +=  -I./includes -I/usr/X11R6/include -I./lib/irrlicht/include -I./includes/LuaBridge -I/usr/include/lua5.1 -I./lib/irrKlang/include

CPPFLAGS    =	$(INCLUDEPATH) -O3 -ffast-math -std=c++11 -g3

CPP         =	g++

LIBS        =	-lX11 -lXcursor -lpthread -lIrrlicht -llua5.1 ./lib/irrKlang/bin/linux-gcc-64/libIrrKlang.so

all:		$(NAME)

$(NAME)	    :	$(OBJ)
		$(CPP) $(OBJ) -o $(NAME) $(LIBS)

clean       :
		rm -f $(OBJ)

fclean      :	clean
		rm -f $(NAME)

re          :	fclean all


