#include "Input.hpp"
#include "../Game.hpp"
#include "../Physics/Point.hpp"

Input* Input::g_Instance = nullptr;

Input::Input()
{
    gKey_States = SDL_GetKeyboardState(nullptr);
}

bool Input::No_Key_Down()
{
    SDL_Scancode Key_List [] = {SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_I, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_ESCAPE,SDL_SCANCODE_SPACE};
    for (SDL_Scancode key : Key_List){
        if (gKey_States[key] == 1){
            return false;
        }
    }
    return true;
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
            Game::Get_Instance()->Quit();
            break;
        case SDL_KEYDOWN:
            Key_Down();
            break;
        case SDL_KEYUP:
            Key_Up();
            break;
        case SDL_MOUSEMOTION:
            gEvent_Type = SDL_MOUSEMOTION;
            break;
        case SDL_MOUSEBUTTONDOWN:
            gEvent_Type = SDL_MOUSEBUTTONDOWN;
            break;
        case SDL_MOUSEBUTTONUP:
            gEvent_Type = SDL_MOUSEBUTTONUP;
            break;
        default:
            break;
        }
    }
}

SDL_EventType Input::Get_Event_Type()
{
    return gEvent_Type;
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

Point Input::Get_Mouse_Position()
{
    int x; int y;
    SDL_GetMouseState( &x, &y );
    Point MP(x, y);
    return MP;
}