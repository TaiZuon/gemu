#include "Setting.hpp"
#include "Game.hpp"
#include "SoundManager/Sound.hpp"
#include "Intro.hpp"
#include "About.hpp"

Setting::Setting()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    
    gIs_Back = false;
    gIs_Mute = false;
    gIs_Intro = false;
    gIs_About = false;
}

void Setting::Back()
{
    Game::Get_Instance()->PopState();
}

void Setting::OpenIntro()
{
    Game::Get_Instance()->ChangeState(new Intro());
}

void Setting::OpenAbout()
{
    Game::Get_Instance()->ChangeState(new About());
}

void Setting::Mute()
{
    Sound::Get_Instance()->Mute();
}
void Setting::UnMute()
{
    Sound::Get_Instance()->UnMute();
}
bool Setting::Init()
{
    int pos_y = 300;
    mBack = new Button(new Properties("Back",SCREEN_WIDTH - 100, 5, 80, 80, SDL_FLIP_NONE));
    mSound = new Button(new Properties("Sound_On",SCREEN_WIDTH / 2 - 70, pos_y, 141, 64, SDL_FLIP_NONE));
    mAbout = new Button(new Properties("About",SCREEN_WIDTH / 2 - 70, pos_y + 70, 141, 64, SDL_FLIP_NONE));
    mIntro = new Button(new Properties("Intro",SCREEN_WIDTH / 2 - 70, pos_y + 140, 141, 64, SDL_FLIP_NONE));

    return true;
}

void Setting::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);

    TextureManager::Get_Instance()->Draw("Setting_bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, nullptr, SDL_FLIP_NONE);

    mBack->Draw();
    mSound->Draw();
    mAbout->Draw();
    mIntro->Draw();

    SDL_RenderPresent(gGS_Renderer);
}

void Setting::Events()
{
    if(mBack->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Back = true;
    }
    if(mAbout->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_About = true;
        mAbout->Set_Button_State(MOUSE_OUT);
    }
    if(mIntro->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Intro = true;
        mIntro->Set_Button_State(MOUSE_OUT);
    }
    if(!gIs_Mute and mSound->Get_Button_State() == MOUSE_DOWN and mSound->Is_New_State())
    {
        gIs_Mute = true;
        mSound->Set_Props("Sound_Off");
        mSound->Set_Button_State(MOUSE_OUT);
    }
    if(gIs_Mute and mSound->Get_Button_State() == MOUSE_DOWN and mSound->Is_New_State())
    {
        gIs_Mute = false;
        mSound->Set_Props("Sound_On");
        mSound->Set_Button_State(MOUSE_OUT);
    }
}

void Setting::Update()
{
    Events();
    if(!gIs_About and !gIs_Back and !gIs_Intro)
    {
        if(gIs_Mute)
        {
            Mute();
            
        }
        else if(!gIs_Mute)
        {
            UnMute();
            
        }
        mSound->State_Update();
        mBack->State_Update();
        mAbout->State_Update();
        mIntro->State_Update();
        
    }
    else if(gIs_About)
    {
        gIs_About = false;
        SDL_Delay(200);
        OpenAbout();
    }
    else if(gIs_Back)
    {
        gIs_Back = false;
        SDL_Delay(200);
        Back();
    } 
    else if(gIs_Intro)
    {
        gIs_Intro = false;
        SDL_Delay(200);
        OpenIntro();
    }
}
void Setting::Clean()
{
    
}
