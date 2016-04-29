NAME        =	cpp_indie_game

SRC         =	sources/main.cpp	\

OBJ         =	$(SRC:.cpp=.o)

INCLUDEPATH +=  -I./includes -I/usr/X11R6/include -I./lib/irrlicht/include

CPPFLAGS    =	-O3 -ffast-math -lX11 -lXcursor -L./lib/irrlicht/bin -lIrrlicht

CC          =	g++

LIBS        =

$(NAME)     :	all

all         :	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean       :
		rm -f $(OBJ)

fclean      :	clean
		rm -f $(NAME)

re          :	fclean all


