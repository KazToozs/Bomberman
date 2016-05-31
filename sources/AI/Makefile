
SRC	=	./test/main.cpp			\
		./src/AI.cpp			\
		../Player/src/Game.cpp		\
		../Map/Map.cpp			\
		../Player/src/Player.cpp	\
		../Player/src/PowerBomb.cpp	\
		../Player/src/PowerRange.cpp	\
		../Player/src/PowerSpeed.cpp	\
		../Player/src/Bomb.cpp		\
		../Player/src/Keybind.cpp	\

CXXFLAGS=	-g -g3 -I/usr/include/lua5.1 -I../../includes -I../Player/include -I./LuaBridge -std=c++11 

COMP	=	$(SRC:.cpp=.o)

LIB	=	-llua5.1

FLAGS	=	-W -W -Wextra

NAME	=	lua_test

CXX	=	g++

all: $(NAME)

$(NAME): $(COMP)
	$(CXX) -o $(NAME) $(COMP) $(CXXFLAGS) $(LIB)

clean:
	rm -f $(COMP)

fclean: clean
	rm -f $(NAME)

re: fclean all
