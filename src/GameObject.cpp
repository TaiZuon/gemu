#include "GameObject.hpp"
#include "TextureManager.hpp"

// GameObject::GameObject(const char* texturesheet, int x, int y, int vx, int vy)
// {
//     objTexture = TextureManager::LoadTexture(texturesheet);

//     X_Pos = x; 
//     Y_Pos = y;

//     X_Vel = vx;
//     Y_Vel = vy;

//     Up = false; Down = false; Left = false; Right = false;
// }

void GameObject::go_Stop()
{
    X_Vel = 0;
    Y_Vel = 0;
}

void GameObject::go_Up()
{
    Y_Pos -= Y_Vel;
}

void GameObject::go_Down()
{
    Y_Pos += Y_Vel;
}

void GameObject::go_Left()
{
    X_Pos -= X_Vel; 
}

void GameObject::go_Right()
{
    X_Pos += X_Vel;
}

void GameObject::Update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = X_Pos;
    destRect.y = Y_Pos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2; 

}

void GameObject::Render()
{
    SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);
}