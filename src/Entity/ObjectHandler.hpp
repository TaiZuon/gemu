#pragma once

#include "SDL.h"
#include "Characters/Warrior.hpp"
#include "Characters/Orc.hpp"
#include "Characters/Boss.hpp"
#include "../Constant.hpp"

class ObjectHandler
{
private:
    static ObjectHandler* g_Instance;
    int Num_Enemies = 0;
    int Num_Bosses = 0;
    Warrior* Player;
    Orc* Enemy;
    std::vector<Orc*> Enemies;
    Boss* Bosu;
    std::vector<Boss*> Bosses; 

public:
    ObjectHandler(){}
    static ObjectHandler* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new ObjectHandler();
    }
    int Get_Num_Enemies()
    {
        return Num_Enemies;
    }
    int Get_Num_Bosses()
    {
        return Num_Bosses;
    }
    Warrior* Get_Player()
    {
        return Player;
    }
    Orc* Get_Enemy(int i)
    {
        return Enemies[i];
    }
    Boss* Get_Boss(int i)
    {
        return Bosses[i];
    }
    void New_Player(int x, int y);
    void Add_New_Enemy(int x, int y);
    void Add_New_Boss(int x, int y);
    void Delete_Player();
    void Delete_Enemy(int i);
    void Delete_Boss(int i);
    void Delete_All();

};


