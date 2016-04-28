NAME	=	cpp_indie_game

SRC	=	sources/main.cpp	\
		sources/gui.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS =	-I./includes

CC	=	g++

LIBS	=	-lOgreMain -lOIS -lboost_system

$(NAME)	:	all

all:		$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all


