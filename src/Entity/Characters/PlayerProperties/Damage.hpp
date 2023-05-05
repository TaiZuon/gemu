#pragma once

#include "../../../Animation/Animation.hpp"
#include "../../../Constant.hpp"

class Damage
{

public:
    Damage();
    static Damage* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Damage();
    }
    void Update(double dt);
    void Set_Num_Damage(int a) { gNum_Damage = a; }
    void Up_Num_Damage(int a);
    void Save_Num_Damage();
    void Get_Num_Damage();
    int Check_Num_Damage();
    void Draw_Num_Damage();

private:
    static Damage* g_Instance;
    int gNum_Damage;
    Animation* gAnimation;
    int gPrice = 1000;
};
