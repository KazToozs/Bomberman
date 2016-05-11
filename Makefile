NAME        =	cpp_indie_game

SRC         =	sources/main.cpp	\
		sources/Gui/gui.cpp

OBJ         =	$(SRC:.cpp=.o)

INCLUDEPATH +=  -I./includes -I/usr/X11R6/include -I./lib/irrlicht/include

CPPFLAGS    =	$(INCLUDEPATH) -O3 -ffast-math -std=c++11

CPP          =	g++

LIBS        =	-lX11 -lXcursor -lpthread -lIrrlicht

$(NAME)     :	all

all         :	$(OBJ)
		$(CPP) $(LIBS) $(OBJ) -o $(NAME)

clean       :
		rm -f $(OBJ)

fclean      :	clean
		rm -f $(NAME)

re          :	fclean all


