#include "Menu.hpp"
#include "../Game.hpp"
#include "../Inputs/Input.hpp"
#include "Play.hpp"
#include "../Entity/Button/Button.hpp"

Menu::Menu(){}
void Menu::StartGame()
{
    Game::Get_Instance()->ChangeState(new Play());
}

void Menu::Events()
{
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_1))
    {
        StartGame();
    }
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_2))
    {
        Exit();
    }
}

bool Menu::Init()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    Play_Game = new Button(new Properties("Play_Game",200, 200, 141, 64, SDL_FLIP_NONE));
    std::cout << "Menu initialized!\n";
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);
    SDL_RenderClear(gGS_Renderer);

    SDL_SetRenderDrawColor(gGS_Renderer, 200, 0, 0, 255);
    SDL_Rect Box = {100, 100, 100, 100};
    SDL_RenderDrawRect(gGS_Renderer, &Box);

    Play_Game->Draw();

    SDL_RenderPresent(gGS_Renderer);
}

void Menu::Update()
{
    Events();

    Play_Game->State_Update();
}

bool Menu::Exit()
{
    std::cout << "Exit Menu!\n";
    return true;
}

void Menu::Settings(){}

void Menu::Upgrade(){}

void Menu::Quit(){}