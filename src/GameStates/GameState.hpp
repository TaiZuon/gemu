#pragma once

#include "SDL.h"
#include "../Entity/Button/Button.hpp"

class GameState
{
public:
    virtual bool Init()=0;
    virtual bool Exit()=0;

    virtual void Update()=0;
    virtual void Render()=0;

    virtual void Clean()
    {
        SDL_DestroyRenderer(gGS_Renderer);
    }
protected:
    SDL_Renderer* gGS_Renderer;
};

