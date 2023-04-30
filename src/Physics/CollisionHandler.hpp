#pragma once

#include "SDL.h"
#include "Point.hpp"
#include <vector>
#include "../Map/Map.hpp"
#include "../Game.hpp"

class CollisionHandler
{
private:
    static CollisionHandler* g_Instance;
public:
    CollisionHandler(){}
    static CollisionHandler* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new CollisionHandler();
    }
    int Is_Collision(SDL_Rect a, SDL_Rect b); 

    int Is_Seperate_Collision(SDL_Rect orc, SDL_Rect warrior);

    bool Is_Map_Collision(SDL_Rect a);

};

