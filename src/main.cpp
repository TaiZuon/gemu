#include "Game.hpp"
#include "Timer/Timer.hpp"
#include "Map/Map.hpp"
#include "Constant.hpp"

int main(int argv, char** args)
{
    std::cout << "Starting...\n";

    Game::Get_Instance()->Init("Gemu", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Game::Get_Instance()->Load();

//    Map::Get_Instance()->Create_White_Map();
    while( Game::Get_Instance()->running())
    {
        Map::Get_Instance()->Draw();
        Game::Get_Instance()->Handle_Events();
        Game::Get_Instance()->Update(0);
        Game::Get_Instance()->Render();
        Timer::Get_Instance()->Tick();
    }

    Game::Get_Instance()->Clean();
    Game::Get_Instance()->Quit();
    
    return 0;
}