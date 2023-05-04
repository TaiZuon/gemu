#include "Camera.hpp"
#include "iostream"

Camera* Camera::g_Instance = nullptr;

void Camera::Update(double dt)
{
    if(gTarget != nullptr)
    {
//        std::cout << gTarget->X << " " << gTarget->Y << '\n';
        gView_Box.x = gTarget->X - SCREEN_WIDTH * 2 / 4;
        gView_Box.y = gTarget->Y - SCREEN_HEIGHT * 2 / 4;
        
        gView_Box.x = std::max(gView_Box.x, 0);
        gView_Box.y = std::max(gView_Box.y, 0);

        gView_Box.x = std::min(2 * SCREEN_WIDTH - gView_Box.w, gView_Box.x); 
        gView_Box.y = std::min(SCREEN_HEIGHT - gView_Box.h, gView_Box.y);

        gView_Box.h = SCREEN_HEIGHT;
        gView_Box.w = SCREEN_WIDTH;

        gPosition = Vector2D(gView_Box.x, gView_Box.y);
//        std::cout << gPosition.X << " " << gPosition.Y << '\n';
    }
}