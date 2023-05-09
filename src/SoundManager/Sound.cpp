#include "Sound.hpp"

Sound* Sound::g_Instance = nullptr;

void Sound::LoadMusic(std::string id, std::string path)
{
    MusicMap[id] = Mix_LoadMUS(path.c_str());
    if(MusicMap[id] == NULL) std::cout << "Load " << id << " failed!\n";
}
void Sound::LoadEffect(std::string id, std::string path)
{
    EffectMap[id] = Mix_LoadWAV(path.c_str());
    if(EffectMap[id] == NULL) std::cout << "Load " << id << " failed!\n";
}

void Sound::PlayEffect(std::string id)
{
    if(!gIs_Muted)
    Mix_PlayChannel(-1, EffectMap[id], 0);
}

void Sound::PlayMusic(std::string id)
{
    if(!gIs_Muted)
    Mix_PlayMusic(MusicMap[id], -1);
}
void Sound::ChangeMusic(std::string id)
{
    if(Mix_PlayingMusic == 0) PlayMusic(id);
    else 
    {

    }
}

void Sound::LoadAll()
{
    LoadEffect("button_over","assets/Sounds/button_over.wav");
    LoadEffect("Invalid","assets/Sounds/Invalid.wav");
    LoadEffect("Upgrade","assets/Sounds/Upgrade.wav");

    LoadEffect("Running","assets/Sounds/Running.wav");
    LoadEffect("Attack","assets/Sounds/Attack.wav");
    LoadEffect("Dead","assets/Sounds/Dead.wav");

    LoadEffect("Orc_Attack","assets/Sounds/Orc_Attack.wav");
    LoadEffect("Orc_Die","assets/Sounds/Orc_Die.wav");
    LoadEffect("Orc_Insane","assets/Sounds/Orc_Insane.wav");
    LoadEffect("Orc_Laugh","assets/Sounds/Orc_Laugh.wav");

    LoadEffect("Crystal","assets/Sounds/Crystal.wav");

    LoadMusic("bg_music_chill","assets/Sounds/bg_music_chill.wav");
    LoadMusic("bg_music_playgame","assets/Sounds/bg_music_playgame.wav");
    
}

void Sound::Clean()
{
    std::map<std::string, Mix_Chunk*>:: iterator it;
    for(it = EffectMap.begin(); it != EffectMap.end(); it++)
    {
        Mix_FreeChunk(it->second);
    }
    std::map<std::string, Mix_Music*>:: iterator it2;
    for(it2 = MusicMap.begin(); it2 != MusicMap.end(); it2++)
    {
        Mix_FreeMusic(it2->second);
    }
    Mix_Quit();
}