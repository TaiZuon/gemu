#ifndef OBJECT_HANDLER_HPP
#define OBJECT_HANDLER_HPP

#include "SDL.h"
#include "Characters/Warrior.hpp"
#include "Characters/Orc.hpp"
#include "Characters/Boss.hpp"
#include "Items/Heart.hpp"
#include "../Constant.hpp"
#include "Entity/Items/Bullet.hpp"

class ObjectHandler
{
private:
    static ObjectHandler* g_Instance;
    int Num_Enemies = 0;
    int Num_Bosses = 0;
    int Num_Hearts = 0;
    int Num_Crystals = 0;
    
    Warrior* Player;
    Orc* Enemy;
    std::vector<Orc*> Enemies;
    Boss* Bosu;
    std::vector<Boss*> Bosses; 
    Heart* H;
    std::vector<Heart*> Hearts;
    Bullet* Crystal;
    std::vector<Bullet*> Crystals;

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
    int Get_Num_Crystals()
    {
        return Num_Crystals;
    }
    int Get_Num_Heart()
    {
        return Num_Hearts;
    }
    Warrior* Get_Player()
    {
        if(Player != nullptr)
        return Player;
    }
    Orc* Get_Enemy(int i)
    {
        if(Enemies[i] != nullptr)
        return Enemies[i];
    }
    Boss* Get_Boss(int i)
    {
        if(Bosses[i] != nullptr)
        return Bosses[i];
    }
    Bullet* Get_Crystal(int i)
    {
        if(Crystals[i] != nullptr)
        return Crystals[i];
    }
    Heart* Get_Heart(int i)
    {
        return Hearts[i];
    }
    void New_Player(int x, int y);
    void Add_New_Enemy(int x, int y);
    void Add_New_Boss(int x, int y);
    void Add_New_Crystal(int x, int y, int dir, int dam);
    void Add_New_Heart();
    void Delete_Player();
    void Delete_Enemy(int i);
    void Delete_Boss(int i);
    void Delete_Crystal(int i);
    void Delete_Heart(int i);

    bool Is_Clear();

    void Delete_All();

};

#endif

