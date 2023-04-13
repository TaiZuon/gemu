#include "Game.hpp"
#include "Entity/Characters/Warrior.hpp"
#include "TextureManager/TextureManager.hpp"
#include "Inputs/Input.hpp"

Game* Game::g_Instance = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::event;
Warrior* Player = nullptr;

void Game::init(const char * title, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        gRenderer = SDL_CreateRenderer(window, -1, 0);
        if(gRenderer)
        {
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        }
        isRunning = true;
        TextureManager::Get_Instance()->Load("Player","assets/Walk.png");
        Player = new Warrior(new Properties("Player", 100, 100, 128, 128, SDL_FLIP_NONE));
        std::cout << "Game initialized!\n"; 
    }
    else
    {
        std::cout << "Init failed!\n";
    }
}

void Game::handleEvents()
{    
    Input::Get_Instance()->Listen();

}

void Game::update(double dt)
{
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_A))
    {
        SDL_Log("Key A pushed!\n");
    }
    Player->Update(0); 
//    std::cout << "Game updated!\n";
}

void Game::render()
{
    SDL_RenderClear(gRenderer);
    Player->Draw();

    SDL_RenderPresent(gRenderer);
//    std::cout << "Game rendered!\n";
}

void Game::clean()
{
    TextureManager::Get_Instance()->Clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyRenderer(Game::texturemanager->TM_Renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}