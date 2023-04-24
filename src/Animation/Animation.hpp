#pragma once

#include <iostream>
#include "SDL.h"
#include <string>

class Animation
{
private:
    int gSprite_Row, gSprite_Frame;
    int gAnimation_Speed, gFrame_Count;
    std::string gTexture_ID;
    SDL_RendererFlip gFlip;

    
public:

//    bool gRepeat = false;
    double gSum_dt = 0;
    Animation(){}
    void Update(double dt, bool repeat, bool &reset);
    void Draw(double x, double y, int sprite_Width, int sprite_Height);
    void Set_Props(std::string id, int sprite_Row, int Frame_Count, int Animation_Speed, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

 