#include "TextureManager.hpp"
#include "../Game.hpp"

TextureManager* TextureManager::TM_Instance = nullptr;

void TextureManager::Load(std::string id, const char* fileName )
{
    SDL_Surface* tmpSurface = IMG_Load(fileName);
    if(tmpSurface == nullptr) std::cout << "Load failed!\n"; else std::cout << "Img loaded!\n";
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Get_Instance()->Get_Renderer(), tmpSurface);
    SDL_FreeSurface(tmpSurface);
    
    Texture_Map[id] = texture;
}

void TextureManager::Draw(std::string id, SDL_Rect src, SDL_Rect dest, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::Get_Instance()->Get_Renderer(), Texture_Map[id], &src, &dest, angle, center, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row - 1), width, height};
//    std::cout << srcRect.x << " " << srcRect.y << " " << srcRect.w << " " << srcRect.h << "\n";
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(Game::Get_Instance()->Get_Renderer(), Texture_Map[id], &srcRect, &destRect, 0, nullptr, flip);
//    std::cout << "Draw Frame\n";
}
void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(Texture_Map[id]);
    Texture_Map.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator iter;
    for(iter = Texture_Map.begin(); iter != Texture_Map.end(); iter++)
    {
        SDL_DestroyTexture(iter->second);
    }
    Texture_Map.clear();
}