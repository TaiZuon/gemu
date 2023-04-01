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
        void go_Jump();

        bool Up, Down, Left, Right, Jump;

        float X_Vel;
        float Y_Vel;

        float X_Pos;
        float Y_Pos;

        float X_A;
        float Y_A = 0.25;
        
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;


};