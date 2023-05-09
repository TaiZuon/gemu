#pragma once

#include <map>
#include "../TextureManager/TextureManager.hpp"

#define BOSS_BASIC 0
#define ORC_BASIC 1
#define BOSS_ID 2
#define ORC_ID 3

#define INCREASE 1.2

class WaveManager
{
private:
    static WaveManager* g_Instance;
    int gHealth[4];
    int gDamage[4];
    std::map<int, double> Waves; 
    int gNum_Waves = 0;
    int gNum_Enemies;
    int gCurrent_Wave;

public:
    WaveManager()
    {
        Waves[0] = 1;
        gHealth[BOSS_BASIC] = 10000;
        gHealth[ORC_BASIC] = 2500;
        gDamage[BOSS_BASIC] = 50;
        gDamage[ORC_BASIC] = 3;
    }
    static WaveManager* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new WaveManager();
    }
    void Reset_Waves();
    void Generate_Waves(int num_waves);
    void Update_Wave(int wave_id);
    void Next_Wave();
    void Draw_Wave();
    int Get_Boss_Health();
    int Get_Boss_Damage();
    int Get_Orc_Health();
    int Get_Orc_Damage();
    int Get_Current_Wave();
};

