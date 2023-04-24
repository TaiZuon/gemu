#pragma once

#include "SDL.h"
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
    bool Is_Collision(SDL_Rect a, SDL_Rect b);
    bool Is_Map_Collision(SDL_Rect a);

};

