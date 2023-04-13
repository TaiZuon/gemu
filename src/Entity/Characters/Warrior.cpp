#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"

Warrior::Warrior(Properties* props): Character(props)
{
    // gRow = 1;
    // gFrame_Count = 6;
    // gAnimation_Speed = 80;
    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 6, 80, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
//    TextureManager::Get_Instance()->DrawFrame(gTexture_ID, gTransform->X, gTransform->Y, gWidth, gHeight, gRow, gFrame, gFlip);
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
}

void Warrior::Update(double dt)
{
//    gFrame = (SDL_GetTicks() / gAnimation_Speed) % gFrame_Count;
//    std::cout << gFrame << '\n';
    gAnimation->Update();
}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Clean();
}