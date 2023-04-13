#include "Animation.hpp"
#include "../TextureManager/TextureManager.hpp"

void Animation::Update()
{
    gSprite_Frame = (SDL_GetTicks() / gAnimation_Speed) % gFrame_Count;
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