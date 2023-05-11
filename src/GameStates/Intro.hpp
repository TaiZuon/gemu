#pragma once

#include <iostream>
#include "GameState.hpp"

class Intro : public GameState
{
private:
    void Load_Intro();
    void Draw_Intro();
    void Back();

    int Num_lines = 0;
    bool gIs_Back;
public:
    Intro();
    void Events();

    virtual bool Init();

    virtual void Clean();
    virtual void Update();
    virtual void Render();

    Button* mBack = nullptr;

};
