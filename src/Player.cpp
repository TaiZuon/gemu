#include "Player.hpp"
#include "TextureManager.hpp"

Player::Player(const char* texturesheet, int x, int y, int vx, int vy)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    X_Pos = x; 
    Y_Pos = y;

    X_Vel = vx;
    Y_Vel = vy;

    Up = false; Left = false; Right = false;
    if(!Player::isGround()) Down = true; else Down = false;
}

bool Player::isGround()
{
    if((float)Y_Pos == 14 * 32) is_ground = true;
    else is_ground = false;
    return is_ground;
}