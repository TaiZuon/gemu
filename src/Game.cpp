#include "Game.hpp"
#include "Entity/Characters/Warrior.hpp"
#include "TextureManager/TextureManager.hpp"
#include "Inputs/Input.hpp"
#include "Timer/Timer.hpp"

Game* Game::g_Instance = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::event;
Warrior* Player = nullptr;

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
        Player = new Warrior(new Properties("Warrior_Idle", 100, 100, 96, 96, SDL_FLIP_NONE));
        std::cout << "Game initialized!\n"; 
    }
    else
    {
        std::cout << "Init failed!\n";
    }
}

void Game::Handle_Events()
{    
    Input::Get_Instance()->Listen();

}

void Game::Update(double dt)
{
    dt = Timer::Get_Instance()->Get_Delta_Time();
    Player->Update(dt); 
//    std::cout << "Game updated!\n";
}

void Game::Render()
{
    SDL_RenderClear(gRenderer);
    Player->Draw();

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
}

void Game::Quit()
{

}