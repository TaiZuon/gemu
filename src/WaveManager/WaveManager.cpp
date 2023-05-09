#include "WaveManager.hpp"
#include "../Constant.hpp"

WaveManager* WaveManager::g_Instance = nullptr;

void WaveManager::Reset_Waves()
{
    gCurrent_Wave = 0;
}

void WaveManager::Generate_Waves(int num_waves)
{
    for(int i = 1; i <= num_waves; i++)
    {
        Waves[i] = Waves[i - 1]*INCREASE;  
    }
}

void WaveManager::Update_Wave(int wave_id)
{
    gCurrent_Wave = wave_id;
    gHealth[BOSS_ID] = gHealth[BOSS_BASIC] * Waves[wave_id];
    gHealth[ORC_ID] = gHealth[ORC_BASIC] * Waves[wave_id];

    gDamage[BOSS_ID] = gDamage[BOSS_BASIC] * Waves[wave_id];
    gDamage[ORC_ID] = gDamage[ORC_BASIC] * Waves[wave_id];
}

void WaveManager::Next_Wave()
{
    gCurrent_Wave++;
}
int WaveManager::Get_Boss_Health()
{
    return gHealth[BOSS_ID];
}
int WaveManager::Get_Boss_Damage()
{
    return gDamage[BOSS_ID];
}
int WaveManager::Get_Orc_Health()
{
    return gHealth[ORC_ID];
}
int WaveManager::Get_Orc_Damage()
{
    return gDamage[ORC_ID];
}

int WaveManager::Get_Current_Wave()
{
    return gCurrent_Wave;
}
void WaveManager::Draw_Wave()
{
    int n = gCurrent_Wave + 1;
    std::string s = "WAVE " + std::to_string(n);
    TextureManager::Get_Instance()->LoadText("Current_Wave", s);
    TextureManager::Get_Instance()->DrawText("Current_Wave", SCREEN_WIDTH/2 - 50, 5, 0, nullptr, SDL_FLIP_NONE);
}
