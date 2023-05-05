#pragma once

#include "SDL.h"
#include <iostream>
#include "GameState.hpp"

class Upgrade: public GameState
{
private:
    static void Back();

    bool gIs_Back;
    bool gUp_Health;
    bool gUp_Damage;
public:
    Upgrade();
    void Events();

    virtual bool Init();

    virtual void Clean();
    virtual void Update();
    virtual void Render();

    Button* mBack = nullptr;
    Button* mUpHealth = nullptr;
    Button* mUpDamage = nullptr;

};