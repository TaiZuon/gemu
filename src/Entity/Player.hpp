#pragma once 

#include "GameObject.hpp"

class Player : public GameObject{
public:
    Player(const char* texturesheet, int x, int y, int vx, int vy);
    bool isGround();
    void UpSpeed();
    bool is_ground;
};