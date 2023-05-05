#pragma once

#include "../../../Animation/Animation.hpp"
#include "../../../Constant.hpp"

class Health
{

public:
    Health();
    static Health* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Health();
    }
    void Update(double dt);
    void Set_Num_Health(int a) { gNum_Health = a; }
    void Up_Num_Health(int a);
    void Save_Num_Health();
    void Get_Num_Health();
    int Check_Num_Health();
    void Draw_Num_Health();

private:
    static Health* g_Instance;
    int gNum_Health;
    Animation* gAnimation;
    int gPrice = 1000;
};
