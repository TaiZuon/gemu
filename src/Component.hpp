#pragma once
#include "ECS.hpp"

class PositionComponent : public Component
{
private:
    int X_Pos;
    int Y_Pos;
public:

    int x(){return X_Pos;}
    int y(){return Y_Pos;}

    void init() override
    {
        X_Pos = 0;
        Y_Pos = 0;
    }

    void update() override
    {
        X_Pos++;
        Y_Pos++;
    }

    void setPos(int x, int y)
    {
        X_Pos = x;
        Y_Pos = y;
    }
};