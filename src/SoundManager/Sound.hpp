#pragma once

#include <iostream>
#include <map>
#include <string>
#include "SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048

class Sound
{
private:
    static Sound* g_Instance;
    std::map<std::string, Mix_Chunk*> EffectMap;
    std::map<std::string, Mix_Music*> MusicMap;
    bool gIs_Playing_Music;
    bool gIs_Pause_Music;
    bool gIs_Muted;    
public:
    Sound()
    {
        gIs_Playing_Music = false;
        gIs_Pause_Music = false;
    }

    static Sound* Get_Instance()
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Sound();
    }
    void Mute();
    void UnMute();
    void PlayMusic(std::string id);
    void ChangeMusic(std::string id);

    void StopMusic(std::string id);
    void PauseMusic(std::string id);
    void ResumeMusic(std::string id);

    void PlayEffect(std::string id);

    void Set_Mute(bool a)
    {
        gIs_Muted = a;
    }

    void LoadMusic(std::string id, std::string path);
    void LoadEffect(std::string id, std::string path);

    void LoadAll();

    void Clean();

};
