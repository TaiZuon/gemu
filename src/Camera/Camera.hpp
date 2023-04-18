#include "../Physics/Point.hpp"
#include "../Physics/Vector2D.hpp"
#include "SDL.h"
#include "../Constant.hpp"

class Camera
{
private:
    static Camera* g_Instance;
    Point* gTarget;
    Vector2D gPosition;
    SDL_Rect gView_Box;

public:
    Camera()
    {
        gView_Box = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    }

    void Update(double dt);

    static Camera* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Camera();
    }
    SDL_Rect Get_View_Box()
    {
        return gView_Box;
    }
    Vector2D Get_Position()
    {
        return gPosition;
    }
    void Set_Target(Point* Target) 
    {
        gTarget = Target;
    }

};
