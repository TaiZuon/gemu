#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Menu: public GameState
{
private:
    static void NewGame();
    static void OpenSetting();
    static void OpenUpgrade();
    static void OpenExit();

    bool gIs_NewGame;
    bool gIs_Setting;
    bool gIs_Upgrade;
    bool gIs_Exit;

public:
    Menu();
    void Events();
    virtual bool Init();

    virtual void Update();
    virtual void Render();
    virtual void Clean();

    Button* mNewGame = nullptr;
    Button* mSetting = nullptr;
    Button* mUpgrade = nullptr;
    Button* mExit = nullptr;

};
