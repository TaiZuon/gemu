#pragma once

#include "Game.hpp"

class GameObject
{
    public:
//        GameObject(const char* texturesheet, int x, int y, int vx, int vy);
//       ~GameObject();

        void Update();
        void Render();
        void go_Up();
        void go_Down();
        void go_Left();
        void go_Right();
        void go_Stop();

        bool Up, Down, Left, Right;

        int X_Vel;
        int Y_Vel;

        int X_Pos;
        int Y_Pos;
        
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;


};