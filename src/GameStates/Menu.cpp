#include "Menu.hpp"
#include "../Game.hpp"
#include "../Inputs/Input.hpp"
#include "Play.hpp"
#include "../Entity/Button/Button.hpp"
#include "../Entity/ObjectHandler.hpp"
#include "Upgrade.hpp"
#include "../Camera/Camera.hpp"
#include "../SoundManager/Sound.hpp"
#include "Setting.hpp"

Menu::Menu()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    gIs_NewGame = false;
    gIs_Setting = false;
    gIs_Upgrade = false;
    gIs_Exit = false;
}
void Menu::NewGame()
{
    Game::Get_Instance()->ChangeState(new Play());
}

void Menu::OpenUpgrade()
{
    Game::Get_Instance()->ChangeState(new Upgrade());
}
void Menu::OpenExit()
{
    std::cout << "Exit!\n";
    Game::Get_Instance()->Clean();
    Game::Get_Instance()->Quit();
}

void Menu::Events()
{
    if(mNewGame->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_NewGame = true;
        mNewGame->Set_Button_State(MOUSE_OUT);

    }
    if(mExit->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Exit = true;
        mExit->Set_Button_State(MOUSE_OUT);
    }
    if(mUpgrade->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Upgrade = true;
        mExit->Set_Button_State(MOUSE_OUT);
    }
    if(mSetting->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Setting = true;
        mSetting->Set_Button_State(MOUSE_OUT);
    }
}

bool Menu::Init()
{
    if(!ObjectHandler::Get_Instance()->Is_Clear()) ObjectHandler::Get_Instance()->Delete_All();
    
    int pos_y = 300; 
    mNewGame = new Button(new Properties("NewGame",SCREEN_WIDTH / 2 - 70, pos_y, 141, 64, SDL_FLIP_NONE));
    mSetting = new Button(new Properties("Setting",SCREEN_WIDTH / 2 - 70, pos_y + 70, 141, 64, SDL_FLIP_NONE));
    mUpgrade = new Button(new Properties("Upgrade",SCREEN_WIDTH / 2 - 70, pos_y + 140, 141, 64, SDL_FLIP_NONE));
    mExit = new Button(new Properties("Exit",SCREEN_WIDTH / 2 - 70, pos_y + 210, 141, 64, SDL_FLIP_NONE));

    Sound::Get_Instance()->PlayMusic("bg_music_chill");

    std::cout << "Menu initialized!\n";
    return true;
}

void Menu::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);

    TextureManager::Get_Instance()->Draw("Menu_bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, nullptr, SDL_FLIP_NONE);

    mNewGame->Draw();
    mSetting->Draw();
    mUpgrade->Draw();
    mExit->Draw();

    SDL_RenderPresent(gGS_Renderer);
}

void Menu::Update()
{
    Events();
    if(!gIs_Exit and !gIs_NewGame and !gIs_Setting and !gIs_Upgrade)
    {
        mNewGame->State_Update();
        mSetting->State_Update();
        mUpgrade->State_Update();
        mExit->State_Update();
    } 
    else
    {
        if(gIs_NewGame)
        {
            gIs_NewGame = false;
            SDL_Delay(200);
            NewGame();
        }
        if(gIs_Setting)
        {
            gIs_Setting = false;
            SDL_Delay(200);
            OpenSetting();
        }
        if(gIs_Upgrade) 
        {
            mUpgrade->Set_Button_State(MOUSE_OUT);
            gIs_Upgrade = false;
            SDL_Delay(200);
            OpenUpgrade();
        }
        if(gIs_Exit) 
        {
            gIs_Exit = false;
            SDL_Delay(200);
            OpenExit();
        }
    }
}

void Menu::OpenSetting()
{
    Game::Get_Instance()->ChangeState(new Setting());
}

void Menu::Clean()
{
    delete mNewGame;
    delete mSetting;
    delete mUpgrade;
    delete mExit;
} 