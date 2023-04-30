#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Play: public GameState
{
private:
    static void OpenMenu();
    static void PauseGame();

    bool gIs_Setting;
    
public:
    Play();
    void Events();
    virtual bool Init();
    virtual bool Exit();

    virtual void Update();
    virtual void Render();
};
