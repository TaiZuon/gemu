#include "Game.hpp"
#include "Entity/Characters/Warrior.hpp"
#include "Entity/Characters/Orc.hpp"
#include "TextureManager/TextureManager.hpp"
#include "Inputs/Input.hpp"
#include "Timer/Timer.hpp"
#include "Map/Map.hpp"
#include "Camera/Camera.hpp"
#include "Physics/CollisionHandler.hpp"


Game* Game::g_Instance = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::event;
Warrior* Player = nullptr;
Orc* Enemy = nullptr;
std::vector<Orc*> Enemies;
int Num_Enemies = 4;

void Game::Init(const char * title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
        if(gRenderer)
        {
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
        }
        gIs_Running = true;
        
        TextureManager::Get_Instance()->Load("Warrior_Idle","assets/Characters/Warriors/Warrior_1/Idle.png");
        TextureManager::Get_Instance()->Load("Warrior_Run","assets/Characters/Warriors/Warrior_1/Run.png");
        TextureManager::Get_Instance()->Load("Warrior_Dead","assets/Characters/Warriors/Warrior_1/Dead.png");
        TextureManager::Get_Instance()->Load("Warrior_Jump","assets/Characters/Warriors/Warrior_1/Jump.png");
        TextureManager::Get_Instance()->Load("Warrior_Fall","assets/Characters/Warriors/Warrior_1/Fall.png");

        TextureManager::Get_Instance()->Load("Warrior_Hurt","assets/Characters/Warriors/Warrior_1/Hurt.png");
        TextureManager::Get_Instance()->Load("Warrior_Walk","assets/Characters/Warriors/Warrior_1/Walk.png");
        TextureManager::Get_Instance()->Load("Warrior_Attack_1","assets/Characters/Warriors/Warrior_1/Attack_1.png");
        TextureManager::Get_Instance()->Load("Warrior_Attack_2","assets/Characters/Warriors/Warrior_1/Attack_2.png");
        TextureManager::Get_Instance()->Load("Warrior_Attack_3","assets/Characters/Warriors/Warrior_1/Attack_3.png");
        
        
        TextureManager::Get_Instance()->Load("Orc_Idle","assets/Characters/Orcs/Orc_Berserk/Idle.png");
        TextureManager::Get_Instance()->Load("Orc_Run","assets/Characters/Orcs/Orc_Berserk/Run.png");
        TextureManager::Get_Instance()->Load("Orc_Hurt","assets/Characters/Orcs/Orc_Berserk/Hurt.png");
        TextureManager::Get_Instance()->Load("Orc_Dead","assets/Characters/Orcs/Orc_Berserk/Dead.png");
        TextureManager::Get_Instance()->Load("Orc_Attack_1","assets/Characters/Orcs/Orc_Berserk/Attack_1.png");


        TextureManager::Get_Instance()->Load("Background","assets/Map/Background.png");
        Player = new Warrior(new Properties("Warrior_Idle", 100, 100, 96, 96, SDL_FLIP_NONE));
        
        for (int i = 0; i < Num_Enemies; i++)
        {
        Enemy = new Orc(new Properties("Orc_Idle", 200 * i, 100, 96, 96, SDL_FLIP_NONE));
        Enemies.push_back(Enemy);
        }
        std::cout << "Game initialized!\n";

        Camera::Get_Instance()->Set_Target(Player->Get_Origin());

    }
    else
    {
        std::cout << "Init failed!\n";
    }
}

void Game::Load() 
{
    Map::Get_Instance()->Create_White_Map();
    Map::Get_Instance()->Read_Map();
//    Map::Get_Instance()->Print_MapMatrix();
    TextureManager::Get_Instance()->Load("Tile_02","assets/Map/Tiles/Tile_02.png");
    TextureManager::Get_Instance()->Load("Tile_12","assets/Map/Tiles/Tile_12.png");

}

void Game::Handle_Events()
{    
    Input::Get_Instance()->Listen();

}

void Game::Update(double dt)
{
    dt = Timer::Get_Instance()->Get_Delta_Time();
    for(int i = 0; i < Num_Enemies; i++)
    {
    Enemies[i]->Set_Tar_Box(Player->Get_Collider()->Get_Box());
    Enemies[i]->Set_Tar(Player->Get_Origin());
    Enemies[i]->Set_Tar_Dam(Player->Get_Damage());
    Enemies[i]->Set_Tar_State(Player->Is_Attacking());
    Enemies[i]->Update(dt);
    }
    Player->Set_Enemy_Dam(0);
    for(int i = 0; i < Num_Enemies; i++)
    {
    if(Enemies[i]->Is_Tar_Colly())    
    Player->Up_Enemy_Dam(Enemies[i]->Get_Damage());
    Player->Set_Enemy_State(Enemies[i]->Is_Attacking());
    }
    Player->Update(dt); 
    Camera::Get_Instance()->Update(dt);
//    std::cout << "Game updated!\n";
}

void Game::Render()
{
    SDL_RenderClear(gRenderer);
    TextureManager::Get_Instance()->DrawBackGround("Background", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
    Map::Get_Instance()->Draw();
    for( int i = 0; i < Num_Enemies; i++)
    Enemies[i]->Draw();
    Player->Draw();
//    std::cout << CollisionHandler::Get_Instance()->Is_Map_Collision(Player->Get_Box());
    
//    TextureManager::Get_Instance()->Draw("Tile_02", 100, 100, 32, 32, 0, nullptr, SDL_FLIP_NONE);

    SDL_RenderPresent(gRenderer);
//    std::cout << "Game rendered!\n";
}

void Game::Clean()
{
    TextureManager::Get_Instance()->Clean();
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    SDL_Quit();
    
    std::cout << "Game cleaned!\n";
    exit(0);
}

void Game::Quit()
{

}