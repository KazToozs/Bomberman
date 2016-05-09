NAME        =	cpp_indie_game

SRC         =	sources/main.cpp	\
		sources/gui.cpp

OBJ         =	$(SRC:.cpp=.o)

INCLUDEPATH +=  -I./includes -I/usr/X11R6/include -I./lib/irrlicht/include

CPPFLAGS    =	$(INCLUDEPATH) -O3 -ffast-math -std=c++11

CC          =	g++

LIBS        =	-lIrrlicht -lX11 -lXcursor -lpthread

$(NAME)     :	all

all         :	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean       :
		rm -f $(OBJ)

fclean      :	clean
		rm -f $(NAME)

re          :	fclean all


