#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Menu: public GameState
{
private:
    static void NewGame();
    static void Settings();
    static void Upgrade();

public:
    Menu();
    void Events();
    virtual bool Init();
    virtual bool Exit();

    virtual void Update();
    virtual void Render();
    virtual void Clean();

    Button* mNewGame = nullptr;
    Button* mSetting = nullptr;
    Button* mUpgrade = nullptr;
    Button* mExit = nullptr;

};
