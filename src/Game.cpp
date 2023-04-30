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

void Game::ChangeState(GameState* Target)
{

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
        gIs_Running = true;

        gStates.push_back(new Play());
        gStates[0]->Init();

        // TextureManager::Get_Instance()->LoadAll();   

        // ObjectHandler::Get_Instance()->New_Player(100, 200);

        // ObjectHandler::Get_Instance()->Add_New_Boss(400, 200);
        // std::cout << "New Boss!\n";
        // srand(time(0));
        // for (int i = 0; i < Num_Enemies; i++)
        // {

        //     int MAX = 600, MIN = 0;
        //     int posX = rand() % (MAX - MIN + 1) + MIN;

        //     ObjectHandler::Get_Instance()->Add_New_Enemy(posX, 100);
        // }
        // std::cout << "Game initialized!\n";

        // Camera::Get_Instance()->Set_Target(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
    }
    else
    {
        std::cout << "Init failed!\n";
    }
}

void Game::Load() 
{
    Coin::Get_Instance()->Get_Num_Coins();
    Coin::Get_Instance()->Check_Num_Coins();
//    Coin::Get_Instance()->Update(0);

    Map::Get_Instance()->Create_White_Map();
    Map::Get_Instance()->Read_Map();
//    Map::Get_Instance()->Print_MapMatrix();
//  TextureManager::Get_Instance()->Load("Tile_02","assets/Map/Tiles/Tile_02.png");
//    TextureManager::Get_Instance()->Load("Tile_12","assets/Map/Tiles/Tile_12.png");

}

void Game::Handle_Events()
{    
    Input::Get_Instance()->Listen();

}

void Game::Update(double dt)
{
    gStates[0]->Update();

//     int blocked_back = 0;
//     int blocked_fore = 0;
//     dt = Timer::Get_Instance()->Get_Delta_Time();
//     ObjectHandler::Get_Instance()->Get_Boss(0)->Update(dt);
// //    std::cout << "Boss updated!\n";
//     for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
//     {
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Dir(ObjectHandler::Get_Instance()->Get_Player()->Get_Dir());
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Origin(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Dam(ObjectHandler::Get_Instance()->Get_Player()->Get_Damage());
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_State(ObjectHandler::Get_Instance()->Get_Player()->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Player()->Is_Dead());
//         ObjectHandler::Get_Instance()->Get_Enemy(i)->Update(dt);
//     }
//     ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_Dam(0);
//     for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
//     {
//         ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_State(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Dead());
// //        std::cout << "Orc " << i << ": " << Enemies[i]->Is_Attacking() << '\n';
// //        std::cout << i << " " << Enemies[i]->Is_Tar_Colly() << '\n';
//         if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Tar_Colly() != 0)  
//         {

// //            std::cout << "Orc " << i << ": " << Enemies[i]->Is_Attacking() << '\n';
//             ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_Dam(ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Damage());
//             ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Damage());
            
// //            std::cout << Enemies[i]->Is_Tar_Colly() << '\n';

//  //           Player->Block();
//             switch (ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Tar_Colly())
//             {
//             case FORWARD:
//                 if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == BACKWARD) blocked_back--;
//                 break;
//             case BACKWARD:
//                 if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == FORWARD) blocked_fore++;
//                 break;
//             default:
//                 break;
//             }
//         }
//         if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Killed()) 
//         {
// //            std::cout << "killed\n";
//             ObjectHandler::Get_Instance()->Delete_Enemy(i);    
//         }
        
//     }
//     if(blocked_back != 0) ObjectHandler::Get_Instance()->Get_Player()->Block_Backward();
//     if(blocked_fore != 0) ObjectHandler::Get_Instance()->Get_Player()->Block_Forward();
//     ObjectHandler::Get_Instance()->Get_Player()->Update(dt); 
    
//     Camera::Get_Instance()->Update(dt);
//    std::cout << "Game updated!\n";
}

void Game::Render()
{
    gStates[0]->Render();
//     SDL_RenderClear(gRenderer);
//     TextureManager::Get_Instance()->DrawBackGround("Background", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
//     Map::Get_Instance()->Draw();
//     ObjectHandler::Get_Instance()->Get_Boss(0)->Draw();
//     for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
//     ObjectHandler::Get_Instance()->Get_Enemy(i)->Draw();
//     ObjectHandler::Get_Instance()->Get_Player()->Draw();
// //    std::cout << CollisionHandler::Get_Instance()->Is_Map_Collision(Player->Get_Box());
    
// //    TextureManager::Get_Instance()->Draw("Tile_02", 100, 100, 32, 32, 0, nullptr, SDL_FLIP_NONE);

//     SDL_RenderPresent(gRenderer);
// //    std::cout << "Game rendered!\n";
    Coin::Get_Instance()->Save_Num_Coins();
}

void Game::Clean()
{
    TextureManager::Get_Instance()->Clean();

    SDL_DestroyRenderer(gRenderer);
    SDL_Quit();
    delete gPlayer;
    delete gEnemy;
    for (int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++) delete ObjectHandler::Get_Instance()->Get_Enemy(i);
    delete gBosu;
    ObjectHandler::Get_Instance()->Delete_All();
    
    std::cout << "Game cleaned!\n";

}

void Game::Quit()
{
    SDL_DestroyWindow(gWindow);
    exit(0);
}