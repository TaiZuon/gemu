#include "Game.hpp"

int main(int argv, char** args)
{
    std::cout << "Starting...\n";
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    
    int cnt = 0;

    Game::Get_Instance()->init("Gemu", 800, 640, 0);

    while( Game::Get_Instance()->running())
    {
//        std::cout << cnt << " Running...\n" ;
//        frameStart = SDL_GetTicks();

        Game::Get_Instance()->handleEvents();
        Game::Get_Instance()->update(0);
        Game::Get_Instance()->render();

        // frameTime = SDL_GetTicks() - frameStart;

        // if(frameDelay > frameTime) 
        // {
        //     SDL_Delay(frameDelay - frameTime);
        // }
//        cnt++;
    }

    Game::Get_Instance()->clean();
    return 0;
}