#include "SDL.h"

class Input
{
private:
    static Input* g_Instance;

    void Key_Up();
    void Key_Down();

    const Uint8* gKey_States;

public:
    Input();
    static Input* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Input();
    }

    void Listen();
    bool Get_Key_Down(SDL_Scancode Key);
    bool Get_Key_Up(SDL_Scancode Key);
    
};


