#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <map>

class TextureManager
{
    public:
        TextureManager(){}

        static TextureManager* Get_Instance()
        {
            return TM_Instance = (TM_Instance != nullptr)? TM_Instance : new TextureManager();
        }
        void Load(std::string id, const char* fileName);
        void LoadAll();
        void Drop(std::string id);
        void Clean();
        void Draw(std::string id, int x, int y, int width, int height, double angle, const SDL_Point *center, SDL_RendererFlip flip);
        void DrawBackGround(std::string id, int x, int y, int width, int height, double angle, const SDL_Point *center, SDL_RendererFlip flip);
        void DrawTile(std::string id, int x, int y, int tilesize, double angle, const SDL_Point *center, SDL_RendererFlip flip);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void LoadText(std::string id, std::string text);
        void Set_Font(const char* font_name, int size);
        void Set_Text_Color(Uint8 r, Uint8 g, Uint8 b);
        void DrawText(std::string id, int x, int y, double angle, const SDL_Point *center, SDL_RendererFlip flip);
        
    private:
        static TextureManager* TM_Instance;
        std::map<std::string, SDL_Texture*> Texture_Map;
        TTF_Font* gFont;
        SDL_Color gText_Color;
        SDL_Rect gText_Box;
};