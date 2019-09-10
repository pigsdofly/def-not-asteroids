OBJS = src/main.cpp src/game_state.cpp src/game_objects.cpp

CC = g++

#  COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = main.bin

all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

