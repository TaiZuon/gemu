#include "Input.hpp"
#include "../Game.hpp"

Input* Input::g_Instance = nullptr;

Input::Input()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Game::Get_Instance()->Clean();
            break;
        case SDL_KEYDOWN:
            Key_Down();
            break;
        case SDL_KEYUP:
            Key_Up();
            break;
        default:
            break;
        }
    }
}

bool Input::Get_Key_Down(SDL_Scancode Key)
{
    if(gKey_States[Key] == 1) return true;
    return false;
}

bool Input::Get_Key_Up(SDL_Scancode Key)
{
    if(gKey_States[Key] == 0) return true;
    return false;
}

void Input::Key_Up()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}
void Input::Key_Down()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}

int Input::Get_Direction(int Dir)
{
    switch (Dir)
    {
    case HORIZONTAL:
        if(Get_Key_Down(SDL_SCANCODE_D) or Get_Key_Down(SDL_SCANCODE_RIGHT)) return FORWARD; 
        if(Get_Key_Down(SDL_SCANCODE_A) or Get_Key_Down(SDL_SCANCODE_LEFT)) return BACKWARD;
        break;
    case VERTICAL:
        if(Get_Key_Down(SDL_SCANCODE_W) or Get_Key_Down(SDL_SCANCODE_UP)) return FORWARD;
        if(Get_Key_Down(SDL_SCANCODE_S) or Get_Key_Down(SDL_SCANCODE_DOWN)) return BACKWARD;
        break;
    default:
        break;
    }
}