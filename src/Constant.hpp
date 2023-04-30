#pragma once



#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#define JUMP_TIME 1.5f
#define JUMP_FORCE 5.0f
#define RUN_FORCE 1.0f
#define ATTACK_TIME 15.0f

#define UNI_MASS 1.0f
#define GRAVITY 0.2f

#define HORIZONTAL 0
#define VERTICAL 1

#define BACKWARD -1
#define FORWARD 1

#define WARRIOR 0
#define ORC 1
#define MAGE 2
#define BOSS 3

const double MAX_VELOCITIES[4] = {5, 1, 3, 3};
const double MAX_VELOCITY = 3;
const double FRICTION = 0.4;

const int CHAR_SIZE = 96;
const int BOSS_SIZE = 96*2;

const int FPS = 60;
const double DELTA_TIME = 0.15;
