#include "CollisionHandler.hpp"

CollisionHandler* CollisionHandler::g_Instance = nullptr;

bool CollisionHandler::Is_Collision(SDL_Rect a, SDL_Rect b)
{
    bool collx = (a.x < (b.x + b.w)) && (b.x < (a.x + a.w));
    bool colly = (a.y < (b.y + b.h)) && (b.y < (a.y + a.h));

    return (collx && colly);
}

bool CollisionHandler::Is_Map_Collision(SDL_Rect a)
{
    bool collx;
    bool colly = (a.y + a.h >= (Map::Get_Instance()->ID_GROUND)*32);
    return colly;
}

