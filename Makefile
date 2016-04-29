NAME	=	cpp_indie_game

SRC	=	sources/main.cpp	\
                sources/gui.cpp         \
                source/orgretext.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS =	-I./includes -I/usr/local/includes/OGRE/ -I/usr/local/include/OGRE/Overlay

CC	=	g++

LIBS	=	-lOgreMain -lOIS -lboost_system -lpthread

$(NAME)	:	all

all:		$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all


