#include "CollisionHandler.hpp"
#include "../Constant.hpp"
#include <bits/stdc++.h>

CollisionHandler* CollisionHandler::g_Instance = nullptr;

int CollisionHandler::Is_Collision(SDL_Rect a, SDL_Rect b)
{
    bool collx = (a.x - (b.x + b.w) <= 0.1) && (b.x - (a.x + a.w) <= 0.1);

    bool colly = (a.y - (b.y + b.h) <= 0.1) && (b.y - (a.y + a.h) <= 0.1);

    if(collx && colly)
    {
        if(b.x >= a.x) return FORWARD;
        if(b.x < a.x) return BACKWARD;
    } else return 0;
}

bool CollisionHandler::Is_Map_Collision(SDL_Rect a)
{
    bool collx;
    bool colly = (a.y + a.h >= (Map::Get_Instance()->ID_GROUND)*32);
    return colly;
}

int CollisionHandler::Is_Seperate_Collision(SDL_Rect orc, SDL_Rect warrior)
{
    Point orc_origin(orc.x + orc.w/2, orc.y + orc.h/2);
    Point warrior_origin(warrior.x + warrior.w/2, warrior.y + warrior.h/2);

    double distance_x = std::abs(orc_origin.X - warrior_origin.X);
    double distance_y = std::abs(warrior_origin.Y - orc_origin.Y);

    double dmin_x = orc.w/2 + warrior.w/2;
    double dmin_y = orc.h/2 + warrior.h/2;

    if(std::abs(distance_x - dmin_x) <= 0.1 and std::abs(distance_y - dmin_y) <= 0.1)
    {
        if(orc_origin.X - warrior_origin.X >=0)
        return BACKWARD;
        if(orc_origin.X - warrior_origin.X <0)
        return FORWARD;
    }
    return 0;
}

