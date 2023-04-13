#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"

Warrior::Warrior(Properties* props): Character(props)
{
    gRigidBody = new RigidBody();
    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 6, 80, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
}

void Warrior::Update(double dt)
{
    gRigidBody->Update(0.05);
    gTransform->Translate(gRigidBody->Get_Position());

    gAnimation->Update();
}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Clean();
}