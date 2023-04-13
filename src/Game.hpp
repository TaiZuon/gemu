#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
    Game(){}
    static Game* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Game();
    }

    void init(const char * title, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update(double dt);
    void render();
    void clean();

    bool running()
    {
        return isRunning;
    };
    SDL_Renderer* Get_Renderer()
    {
        return gRenderer;
    }

    static SDL_Event event;
    static SDL_Renderer* gRenderer;

private:
    
    
    static Game* g_Instance;
    bool isRunning;
    int cnt = 0;
    SDL_Window* window;
};