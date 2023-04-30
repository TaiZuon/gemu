#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Menu: public GameState
{
private:
    static void StartGame();
    static void Settings();
    static void Upgrade();
    static void Quit();
public:
    Menu();
    virtual bool Init();
    virtual bool Exit();

    virtual void Update();
    virtual void Render();
};
