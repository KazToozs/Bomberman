
SRC	=	./test/main.cpp			\
		../../Player/src/Game.cpp	\
		../../Map/Map.cpp		\
		../../Player/src/Player.cpp

INC	=	-I/usr/incldue/lua5.1

COMP	=	$(SRC:.cpp=.o)

LIB	=	-llua5.1

FLAGS	=	-W -W -Wextra

NAME	=	test

CC	=	g++

all: $(NAME)

$(NAME): $(COMP)
	$(CC) -o $(NAME) $(SRC) $(FLAGS) $(LIB) -std=c++11

clean:
	rm -f $(COMP)

fclean: clean
	rm -f $(NAME)

re: fclean all
