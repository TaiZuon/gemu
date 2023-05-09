#pragma once

#include <iostream>
#include "GameState.hpp"

class Setting: public GameState
{
private:
    static void Back();
    static void OpenMenu();
    static void OpenIntro();
    static void OpenAbout();
    static void Mute();

    bool gIs_Back;
    bool gIs_Menu;
    bool gIs_Mute;
    bool gIs_Intro;
    bool gIs_About;

public:
    Setting();
    void Events();

    virtual bool Init();

    virtual void Clean();
    virtual void Update();
    virtual void Render();

    Button* mBack = nullptr;
    Button* mMenu = nullptr;
    Button* mSound = nullptr;
    Button* mIntro = nullptr;
    Button* mAbout = nullptr;

};