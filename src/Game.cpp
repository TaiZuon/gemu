#include "Game.hpp"
#include "Entity/Characters/Warrior.hpp"
#include "Entity/Characters/Orc.hpp"
#include "TextureManager/TextureManager.hpp"
#include "Inputs/Input.hpp"
#include "Timer/Timer.hpp"
#include "Map/Map.hpp"
#include "Camera/Camera.hpp"
#include "Physics/CollisionHandler.hpp"
#include "Entity/Characters/Boss.hpp"
#include "Entity/Coins/Coin.hpp"
#include "Entity/ObjectHandler.hpp"
#include "GameStates/Menu.hpp"
#include "GameStates/Play.hpp"


Game* Game::g_Instance = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::event;
Warrior* gPlayer = nullptr;
Orc* gEnemy = nullptr;
std::vector<Orc*> gEnemies;
Boss* gBosu = nullptr;
int Num_Enemies = 3;

void Game::PopState()
{
    gStates.erase(gStates.end());
}

void Game::PushState(GameState* Current)
{
    gStates.push_back(Current);
}

void Game::ChangeState(GameState* Target)
{
    bool found = false;
    int Pos;
    for( int i = 0; i < gStates.size(); i++ )
    {
        if(gStates[i] == Target)
        {
            found = true;
            Pos = i;
        }
    }
    if(found)
    {
        while(gStates.size() != Pos) PopState();
    }
    else
    {
        PushState(Target);
    }
//    PushState(Target);
    StateInit();
    std::cout << "Change State!\n";
}

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
        if(TTF_Init() == -1) std::cout << "Init ttf failed!\n"; 
        gIs_Running = true;

        PushState(new Menu());
        gStates[gStates.size()-1]->Init();
        std::cout << gStates.size()-1 << '\n';
    }
    else
    {
        std::cout << "Init failed!\n";
    }
}

void Game::StateInit()
{
    if(!gStates[gStates.size()-1]->Init()) std::cout << "state init failed!\n";
}

void Game::Load() 
{
    Coin::Get_Instance()->Get_Num_Coins();

    Map::Get_Instance()->Create_White_Map();
    Map::Get_Instance()->Read_Map();

    TextureManager::Get_Instance()->Set_Font("assets/Fonts/1.ttf", 30);
    TextureManager::Get_Instance()->Set_Text_Color(255, 255, 255);

    TextureManager::Get_Instance()->LoadAll();
    std::cout << "Game loaded!\n";
}

void Game::Handle_Events()
{    
    Input::Get_Instance()->Listen();
}

void Game::Update(double dt)
{
    gStates[gStates.size()-1]->Update();
}

void Game::Render()
{
    gStates[gStates.size()-1]->Render();

    Coin::Get_Instance()->Save_Num_Coins();
}

void Game::Clean()
{
    TextureManager::Get_Instance()->Clean();

    SDL_DestroyRenderer(gRenderer);
    SDL_Quit();
    // delete gPlayer;
    // delete gEnemy;
    // for (int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++) delete ObjectHandler::Get_Instance()->Get_Enemy(i);
    // delete gBosu;
    ObjectHandler::Get_Instance()->Delete_All();
//    gStates[gStates.size()-1]->Clean();
    
    std::cout << "Game cleaned!\n";

}

void Game::Quit()
{
    SDL_DestroyWindow(gWindow);
    exit(0);
}