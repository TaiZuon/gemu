#OBJS specifies which files to compile as part of the project
OBJS = src\main.cpp src\Game.cpp src\TextureManager\TextureManager.cpp  
OBJS += src\Entity\Characters\Warrior.cpp src\Entity\Characters\Orc.cpp 
OBJS += src\Entity\Characters\Boss.cpp src\Entity\Coins\Coin.cpp 
OBJS += src\Physics\Vector2D.cpp src\Animation\Animation.cpp 
OBJS += src\Inputs\Input.cpp src\Timer\Timer.cpp src\Map\Map.cpp 
OBJS += src\Camera\Camera.cpp src\Physics\CollisionHandler.cpp 
OBJS += src\GameStates\Menu.cpp src\GameStates\Play.cpp src\Entity\ObjectHandler.cpp 
OBJS += src\Entity\Button\Button.cpp src\Entity\Items\Heart.cpp 
OBJS += src\Entity\Characters\PlayerProperties\Health.cpp 
OBJS += src\Entity\Characters\PlayerProperties\Damage.cpp 
OBJS += src\Entity\Items\Bullet.cpp src\GameStates\Upgrade.cpp 
OBJS += src\SoundManager\Sound.cpp src\GameStates\Defeat.cpp 
OBJS += src\WaveManager\WaveManager.cpp src\GameStates\Setting.cpp

#OBJS = $(wildcard *.cpp) 

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I src\SDL\include\SDL2  -I src

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L src\SDL\lib

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gemu

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)