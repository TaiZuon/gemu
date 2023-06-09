#pragma once

#include "SDL.h"
#include "../Constant.hpp"
#include "../Physics/Point.hpp"

class Input
{
private:
    static Input* g_Instance;

    void Key_Up();
    void Key_Down();

    const Uint8* gKey_States;
    SDL_EventType gEvent_Type;
    Point gMouse_Position;

public:
    Input();
    static Input* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Input();
    }

    void Listen();
    bool Get_Key_Down(SDL_Scancode Key);
    bool Get_Key_Up(SDL_Scancode Key);
    bool No_Key_Down();
    int Get_Direction(int Dir);

    SDL_EventType Get_Event_Type();

    Point Get_Mouse_Position();

//    Point gMouse_Position;
    
};


