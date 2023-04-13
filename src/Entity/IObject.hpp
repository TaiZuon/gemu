#pragma once

#include "SDL.h"
#include "SDL_image.h"

class IObject
{
    public:
        virtual void Draw()=0;
        virtual void Update(double dt)=0;
        virtual void Clean()=0;
};