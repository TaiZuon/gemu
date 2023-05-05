#pragma once

#include "SDL.h"
#include "../Entity/Button/Button.hpp"

class GameState
{
public:
    virtual bool Init(){}
    virtual bool Exit(){}

    virtual void Update(){}
    virtual void Render(){}

    virtual void Clean()
    {
        SDL_DestroyRenderer(gGS_Renderer);
    }
protected:
    SDL_Renderer* gGS_Renderer;
};

