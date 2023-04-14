#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"

Warrior::Warrior(Properties* props): Character(props)
{
    gRigidBody = new RigidBody();
    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 6, 40, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
}

void Warrior::Update(double dt)
{
    gAnimation->Set_Props(gTexture_ID, 1, 6, 100, SDL_FLIP_NONE);
    gRigidBody->Unset_Force();

    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_A))
    {
        gAnimation->Set_Props("Warrior_Run", 1, 6, 100, SDL_FLIP_HORIZONTAL);
        gRigidBody->Apply_ForceX(-25);
    }
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_D))
    {
       gAnimation->Set_Props("Warrior_Run", 1, 6, 100, SDL_FLIP_NONE);
       gRigidBody->Apply_ForceX(25);
    }
    gRigidBody->Update(dt);
    gTransform->Translate(gRigidBody->Get_Position());

    gAnimation->Update();
}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Clean();
}