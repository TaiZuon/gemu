#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Defeat: public GameState
{
private: 
    static void NewGame();
    static void OpenMenu();

    bool gIs_NewGame;
    bool gIs_Menu;
public:
    Defeat();
    void Events();
    virtual bool Init();

    virtual void Update();
    virtual void Render();
    virtual void Clean();

    Button* mNewGame;
    Button* mMenu;
};