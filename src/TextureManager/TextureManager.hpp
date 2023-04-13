#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>

class TextureManager
{
    public:
        TextureManager(){}
        static TextureManager* TM_Instance;
        static TextureManager* Get_Instance()
        {
            return TM_Instance = (TM_Instance != nullptr)? TM_Instance : new TextureManager;
        }
        void Load(std::string id, const char* fileName);
        void Drop(std::string id);
        void Clean();
        void Draw(std::string id, SDL_Rect src, SDL_Rect dest, double angle, const SDL_Point *center, SDL_RendererFlip flip);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
    private:
        
        std::map<std::string, SDL_Texture*> Texture_Map;
};