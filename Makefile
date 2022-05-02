OBJS = main.cpp glad.c
OBJ_NAME = main
INC = -I /usr/local/include/SDL2 -I ./include 
all: $(OBJS)
	g++ $(OBJS) -L /usr/local/lib/cmake/SDL2 -l SDL2 $(INC) -o $(OBJ_NAME)
