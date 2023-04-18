#include "SDL.h"

class Collider
{
private:
    SDL_Rect gBox;
    SDL_Rect gEmpty;
public:
    Collider(){}
    SDL_Rect Get_Box()
    {
        return gBox;
    }
    void Set_Empty(int x, int y, int w, int h)
    {
        gEmpty = {x, y, w, h};
    }
    void Set_Box(int x, int y, int w, int h)
    {
        gBox = {
            x - gEmpty.x,
            y - gEmpty.y,
            w - gEmpty.w,
            h - gEmpty.h
        };
    }
};

