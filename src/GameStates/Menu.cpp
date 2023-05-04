#include "Menu.hpp"
#include "../Game.hpp"
#include "../Inputs/Input.hpp"
#include "Play.hpp"
#include "../Entity/Button/Button.hpp"
#include "../Entity/ObjectHandler.hpp"

Menu::Menu(){}
void Menu::NewGame()
{
    Game::Get_Instance()->ChangeState(new Play());
}

void Menu::Events()
{
    if(mNewGame->Get_Button_State() == MOUSE_DOWN)
    {
        SDL_Delay(200);
        NewGame();
        Clean();
    }
    if(mExit->Get_Button_State() == MOUSE_DOWN)
    {
        SDL_Delay(200);
        Exit();
        Clean();
    }
}

bool Menu::Init()
{
    ObjectHandler::Get_Instance()->Delete_All();
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    int pos_x = 250; 
    mNewGame = new Button(new Properties("NewGame",SCREEN_WIDTH / 2 - 70, pos_x, 141, 64, SDL_FLIP_NONE));
    mSetting = new Button(new Properties("Setting",SCREEN_WIDTH / 2 - 70, pos_x + 70, 141, 64, SDL_FLIP_NONE));
    mUpgrade = new Button(new Properties("Upgrade",SCREEN_WIDTH / 2 - 70, pos_x + 140, 141, 64, SDL_FLIP_NONE));
    mExit = new Button(new Properties("Exit",SCREEN_WIDTH / 2 - 70, pos_x + 210, 141, 64, SDL_FLIP_NONE));

    std::cout << "Menu initialized!\n";
    return true;
}

void Menu::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);

    mNewGame->Draw();
    mSetting->Draw();
    mUpgrade->Draw();
    mExit->Draw();

    SDL_RenderPresent(gGS_Renderer);
}

void Menu::Update()
{
    Events();

    mNewGame->State_Update();
    mSetting->State_Update();
    mUpgrade->State_Update();
    mExit->State_Update();
}
bool Menu::Exit()
{
    std::cout << "Exit Menu!\n";
    Game::Get_Instance()->Clean();
    Game::Get_Instance()->Quit();
    return true;
}

void Menu::Settings(){}

void Menu::Upgrade(){}

void Menu::Clean()
{
    delete mNewGame;
    delete mSetting;
    delete mUpgrade;
    delete mExit;
} 