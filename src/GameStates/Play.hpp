#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Play: public GameState
{
private:
    static void OpenMenu();
    static void OpenSetting();
    static void OpenDefeat();

    bool gIs_Setting;
    bool gIs_Defeat;
    
public:
    Play();
    void Events();
    virtual bool Init();
    virtual bool Exit();

    virtual void Update();
    virtual void Render();

    void Init_Player();
    void Init_Orcs();
    void Init_Boss();
    void Init_Other();

    Button* mSetting;
    Button* mMenu;
};
