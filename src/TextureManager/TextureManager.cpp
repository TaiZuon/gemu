#include "TextureManager.hpp"
#include "../Game.hpp"
#include "../Camera/Camera.hpp"

TextureManager* TextureManager::TM_Instance = nullptr;

void TextureManager::Load(std::string id, const char* fileName )
{
    SDL_Surface* tmpSurface = IMG_Load(fileName);
//    if(tmpSurface == nullptr) std::cout << "Load failed!\n"; else std::cout << "Img loaded!\n";
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::Get_Instance()->Get_Renderer(), tmpSurface);
//    if(texture == nullptr) std::cout << "load texture failes!\n"; else std::cout << "Texture loaded!\n";
    SDL_FreeSurface(tmpSurface);
    
    Texture_Map[id] = texture;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    Cam = Cam.ScalarMultiply_Vector(Cam, 1);

    SDL_Rect destRect = {x - (int)Cam.X, y - (int)Cam.Y, width, height};
    SDL_RenderCopyEx(Game::Get_Instance()->Get_Renderer(), Texture_Map[id], &srcRect, &destRect, angle, center, flip);
//    std::cout << id << " drawed!\n"; 
}

void TextureManager::DrawBackGround(std::string id, int x, int y, int width, int height, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    Cam.X *= 0.3;

    SDL_Rect destRect = {x - (int)Cam.X, y - (int)Cam.Y, width, height};
    SDL_RenderCopyEx(Game::Get_Instance()->Get_Renderer(), Texture_Map[id], &srcRect, &destRect, angle, center, flip);
//    std::cout << id << " drawed!\n"; 
}

void TextureManager::DrawTile(std::string id, int x, int y, int tilesize, double angle, const SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, tilesize, tilesize};

    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    SDL_Rect destRect = {x - (int)Cam.X, y - (int)Cam.Y, tilesize, tilesize};
    SDL_RenderCopyEx(Game::Get_Instance()->Get_Renderer(), Texture_Map[id], &srcRect, &destRect, angle, center, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row - 1), width, height};

    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    SDL_Rect destRect = {x - (int)Cam.X, y - (int)Cam.Y, width, height};
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
//        std::cout<<iter->first << "\n";
        SDL_DestroyTexture(iter->second);
    }
    Texture_Map.clear();
}