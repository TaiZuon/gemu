#pragma once

#include <iostream>
#include "SDL.h"
#include <string>

class Animation
{
private:
    int gSprite_Row, gSprite_Frame;
    int gAnimation_Speed, gFrame_Count, gFrame_Num;
    int gLast_Frame;
    bool gNew;
    std::string gTexture_ID;
    SDL_RendererFlip gFlip;
    Uint32 gStart_Time = 0;
    
public:
    double gSum_dt = 0;
    Animation()
    {
        gLast_Frame = 0;
    }
    void Update(double dt, bool repeat, bool &reset);
    void Draw(double x, double y, int sprite_Width, int sprite_Height);
    void Set_Props(std::string id, int sprite_Row, int Frame_Count, int Animation_Speed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void AnimationStart();
    bool Is_Cycle();
    bool Is_New_Frame();
    int Get_Frame();

};

 