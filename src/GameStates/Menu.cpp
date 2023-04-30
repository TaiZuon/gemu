#include "Menu.hpp"
#include "../Game.hpp"
#include "../Inputs/Input.hpp"

Menu::Menu(){}

bool Menu::Init()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    std::cout << "Menu initialized!\n";
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);
    SDL_RenderClear(gGS_Renderer);

    SDL_RenderPresent(gGS_Renderer);
}

void Menu::Update()
{

}

bool Menu::Exit()
{
    std::cout << "Exit Menu!\n";
    return true;
}
void Menu::StartGame(){}

void Menu::Settings(){}

void Menu::Upgrade(){}

void Menu::Quit(){}