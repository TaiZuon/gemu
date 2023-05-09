#pragma once

#include "../GameObject.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "../../Inputs/Input.hpp"
#include "../../Physics/Point.hpp"
#include <string>
#include "SDL.h"

enum ButtonState
{
    MOUSE_OUT=0,
    MOUSE_OVER=1,
    MOUSE_DOWN=2,
    MOUSE_UP=3,
    TOTAL=4
};

class Button: public GameObject
{
public:
    Button(Properties* prop);
    void State_Update();
    virtual void Draw();
    virtual void Clean(){}
    ButtonState Get_Button_State()
    {
        return gButton_State;
    }
    void Set_Button_State(ButtonState target)
    {
        gButton_State = target;
    }
    bool Is_New_State()
    {
        return gNew;
    }
private:
    ButtonState gButton_State;
    int gCurrent_State;
    // ButtonState gCurrent;
    ButtonState gLast;
    bool gNew;
};

