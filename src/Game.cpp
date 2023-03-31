#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Player.hpp"

Player* player;
Player* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game()
{}

Game::~Game()
{}

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
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        isRunning = true;
    }

    player = new Player("assets/player.png", 100, 100, 2, 2);
    enemy = new Player("assets/enemy.png", 100, 0, 1, 1);
    map = new Map();
}

void Game::handleEvents()
{
    
    while(SDL_PollEvent(&event) != 0)
    {
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            //di len
            player->Up = true;
            break;
        case SDLK_s:
            //di xuong
            player->Down = true;
            break;
        case SDLK_a:
            //di trai
            player->Left = true;
            break;
        case SDLK_d:
            //di phai
            player->Right = true;
            break;
        case SDLK_SPACE:
            //dung lai
            player->go_Stop();
            break;
        }
        break;
    case SDL_KEYUP:
    switch (event.key.keysym.sym)
        {
        case SDLK_w:
            //di len
            player->Up = false;
            break;
        case SDLK_s:
            //di xuong
            player->Down = false;
            break;
        case SDLK_a:
            //di trai
            player->Left = false;
            break;
        case SDLK_d:
            //di phai
            player->Right = false;
            break;
        case SDLK_SPACE:
            //dung lai
            player->go_Stop();
            break;
        }
    } 
    }
}

void Game::update()
{
    if( player->isGround()) player->Down = false;
    if( !enemy->isGround()) enemy->go_Down();
    if( player->Up ) player->go_Up();
    if( player->Down ) player->go_Down();
    if( player->Left ) player->go_Left();
    if( player->Right ) player->go_Right();
    player->Update();
    enemy->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
//    std::cout << player->X_Pos << std::endl << player->Y_Pos << '\n'; 
    player->Render();
    enemy->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!\n";
}