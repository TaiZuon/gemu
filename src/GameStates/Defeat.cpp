#include "Defeat.hpp"
#include "../Game.hpp"
#include "Play.hpp"
#include "Menu.hpp"
#include "../Entity/ObjectHandler.hpp"


Defeat::Defeat()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    gIs_NewGame = false;
    gIs_Menu = false;
}

void Defeat::NewGame()
{
    Game::Get_Instance()->ChangeState(new Play());
}
void Defeat::OpenMenu()
{
    Game::Get_Instance()->ChangeState(new Menu());
}

void Defeat::Events()
{
    if(mNewGame->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_NewGame = true;
    }
    if(mMenu->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Menu = true;
    }
}

bool Defeat::Init()
{
    ObjectHandler::Get_Instance()->Delete_All();

    Sound::Get_Instance()->PlayEffect("Orc_Laugh");
    mNewGame = new Button(new Properties("NewGame",SCREEN_WIDTH / 3 - 70, SCREEN_HEIGHT*2/3 + 32, 141, 64, SDL_FLIP_NONE));
    mMenu = new Button(new Properties("Menu",SCREEN_WIDTH*2/3 - 70, SCREEN_HEIGHT*2/3 + 32, 141, 64, SDL_FLIP_NONE));

    std::cout << "Defeat init!\n";
    return true;
}

void Defeat::Update()
{
    Events();
    if(!gIs_NewGame and !gIs_Menu)
    {
        mNewGame->State_Update();
        mMenu->State_Update();
    }
    else
    {
        if(gIs_NewGame)
        {
            gIs_NewGame = false;
            SDL_Delay(200);
            NewGame();
        }
        if(gIs_Menu)
        {
            gIs_Menu = false;
            SDL_Delay(200);
            OpenMenu();
        }
    }
}

void Defeat::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);

    TextureManager::Get_Instance()->Draw("Defeat_bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, nullptr, SDL_FLIP_NONE);

    mNewGame->Draw();
    mMenu->Draw();

    SDL_RenderPresent(gGS_Renderer);
}

void Defeat::Clean()
{

}