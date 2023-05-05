#include "Animation.hpp"
#include "../TextureManager/TextureManager.hpp"

void Animation::Update(double dt, bool repeat, bool &reset)
{
    bool stop = false;

    // if(reset)
    // {
    //     gSprite_Frame = 0;
    //     reset = false;
    // }
    if((gSprite_Frame == gFrame_Count - 1) and !repeat)
    {
        stop = true;
    }
    if(!stop) 
    {
        gSprite_Frame = (SDL_GetTicks() / gAnimation_Speed) % gFrame_Count;
    } 
    else
    {
        gSprite_Frame = gFrame_Count - 1;
    } 
//    std::cout << stop << "\n";
//    std::cout << gSprite_Frame << "\n";
//    std::cout << gFrame_Count << "\n";
}

void Animation::Draw(double x, double y, int Sprite_Width, int Sprite_Height)
{
    TextureManager::Get_Instance()->DrawFrame(gTexture_ID, x, y, Sprite_Width, Sprite_Height, gSprite_Row, gSprite_Frame, gFlip);
}

void Animation::Set_Props(std::string id, int Sprite_Row, int Frame_Count, int Animation_Speed, SDL_RendererFlip Flip)
{
    gTexture_ID = id;
    gSprite_Row = Sprite_Row;
    gFrame_Count = Frame_Count;
    gAnimation_Speed = Animation_Speed;
    gFlip = Flip;
}