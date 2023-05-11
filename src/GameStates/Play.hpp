#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Play: public GameState
{
private:
    static void OpenMenu();
    static void OpenDefeat();

    bool gPause;
    bool gIs_Defeat;
    bool gIs_Menu;
    
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

    Button* mMenu;
    Button* mPause;
};
