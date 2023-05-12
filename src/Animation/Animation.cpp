#include "Animation.hpp"
#include "../TextureManager/TextureManager.hpp"

void Animation::Update(double dt, bool repeat, bool &reset)
{
    int tmp = gSprite_Frame;
    gSprite_Frame = ((SDL_GetTicks() - gStart_Time)/gAnimation_Speed) % gFrame_Num;
    if (tmp != gSprite_Frame)
    { 
        gFrame_Count ++;
        gNew = true;
    }
    else gNew = false;
}

bool Animation::Is_Cycle()
{
    if(gFrame_Count == gFrame_Num) return true;
    return false;
}
bool Animation::Is_New_Frame()
{
    return gNew;
}

int Animation::Get_Frame()
{
    return gSprite_Frame;
}

void Animation::Draw(double x, double y, int Sprite_Width, int Sprite_Height)
{
    TextureManager::Get_Instance()->DrawFrame(gTexture_ID, x, y, Sprite_Width, Sprite_Height, gSprite_Row, gSprite_Frame, gFlip);
}

void Animation::AnimationStart()
{
    gStart_Time = SDL_GetTicks();
    gFrame_Count = 0;
}

void Animation::Set_Props(std::string id, int Sprite_Row, int Frame_Num, int Animation_Speed, SDL_RendererFlip Flip)
{
    gTexture_ID = id;
    gSprite_Row = Sprite_Row;
    gFrame_Num = Frame_Num;
    gAnimation_Speed = Animation_Speed;
    gFlip = Flip;
}