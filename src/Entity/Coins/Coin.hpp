#pragma once

#include "../GameObject.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Constant.hpp"

class Coin
{
public:
    Coin(){}
    static Coin* Get_Instance()
    {
//        std::string a = "Warrior_Idle";
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Coin();
    }
    void Update(double dt){ gNum_Coins += 10; }
    void Set_Num_Coins(int a) { gNum_Coins = a; }
    void Save_Num_Coins();
    void Get_Num_Coins();
    void Check_Num_Coins();
private:
    static Coin* g_Instance;
    int gNum_Coins;
};