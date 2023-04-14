#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Game.cpp TextureManager\TextureManager.cpp  Entity\Characters\Warrior.cpp Physics\Vector2D.cpp Animation\Animation.cpp Inputs\Input.cpp Timer\Timer.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I SDL\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L SDL\lib

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gemu

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)