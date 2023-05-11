#pragma once

#include <iostream>
#include "GameState.hpp"

class About : public GameState
{
private:
    void Load_About();
    void Draw_About();
    void Back();

    int Num_lines = 0;
    bool gIs_Back;
public:
    About();
    void Events();

    virtual bool Init();

    virtual void Clean();
    virtual void Update();
    virtual void Render();

    Button* mBack = nullptr;

};
