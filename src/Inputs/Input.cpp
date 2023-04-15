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

void Input::Key_Up()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}
void Input::Key_Down()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}