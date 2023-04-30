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

void TextureManager::LoadAll()
{
    Load("Warrior_Idle","assets/Characters/Warriors/Warrior_1/Idle.png");
    Load("Warrior_Run","assets/Characters/Warriors/Warrior_1/Run.png");
    Load("Warrior_Dead","assets/Characters/Warriors/Warrior_1/Dead.png");
    Load("Warrior_Jump","assets/Characters/Warriors/Warrior_1/Jump.png");
    Load("Warrior_Fall","assets/Characters/Warriors/Warrior_1/Fall.png");
    Load("Warrior_Hurt","assets/Characters/Warriors/Warrior_1/Hurt.png");
    Load("Warrior_Walk","assets/Characters/Warriors/Warrior_1/Walk.png");
    Load("Warrior_Attack_1","assets/Characters/Warriors/Warrior_1/Attack_1.png");
    Load("Warrior_Attack_2","assets/Characters/Warriors/Warrior_1/Attack_2.png");
    Load("Warrior_Attack_3","assets/Characters/Warriors/Warrior_1/Attack_3.png");
    
    Load("Orc_Idle","assets/Characters/Orcs/Orc_Berserk/Idle.png");
    Load("Orc_Run","assets/Characters/Orcs/Orc_Berserk/Run.png");
    Load("Orc_Hurt","assets/Characters/Orcs/Orc_Berserk/Hurt.png");
    Load("Orc_Dead","assets/Characters/Orcs/Orc_Berserk/Dead.png");
    Load("Orc_Attack_1","assets/Characters/Orcs/Orc_Berserk/Attack_1.png");
    Load("Orc_Warrior_Idle","assets/Characters/Orcs/Orc_Warrior/Idle_1.png");
    
    Load("Background","assets/Map/Background.png");

    Load("Tile_02","assets/Map/Tiles/Tile_02.png");
    Load("Tile_12","assets/Map/Tiles/Tile_12.png");
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