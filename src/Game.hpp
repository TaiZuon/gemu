#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameStates/GameState.hpp"
#include <iostream>
#include <vector>

class Game
{
public:
    Game(){}
    static Game* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Game();
    }

    void Init(const char * title, int width, int height, bool fullscreen);
    
    void StateInit();

    void Load();

    void Handle_Events();
    void Update(double dt);
    void Render();
    void Clean();
    void Quit();

    void PopState();
    void PushState(GameState* Current);
    void ChangeState(GameState* Target);

    bool running()
    {
        return gIs_Running;
    }
    SDL_Renderer* Get_Renderer()
    {
        return gRenderer;
    }

    static SDL_Event event;
    static SDL_Renderer* gRenderer;

private:
    
    static Game* g_Instance;
    bool gIs_Running;
    SDL_Window* gWindow;
    std::vector<GameState*> gStates;
    int gCurrent_State_id = -1;

};