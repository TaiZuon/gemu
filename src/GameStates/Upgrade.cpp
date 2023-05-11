#include "Upgrade.hpp"
#include "../Game.hpp"
#include "Menu.hpp"
#include "../Entity/Characters/PlayerProperties/Damage.hpp"
#include "../Entity/Characters/PlayerProperties/Health.hpp"
#include "../Entity/Coins/Coin.hpp"
#include "../Timer/Timer.hpp"
#include "../SoundManager/Sound.hpp"

Upgrade::Upgrade()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    gIs_Back = false;
}

bool Upgrade::Init()
{
    gUp_Health = false;
    gUp_Damage = false;

    Coin::Get_Instance()->Get_Num_Coins();
    Health::Get_Instance()->Get_Num_Health();
    Damage::Get_Instance()->Get_Num_Damage();

    mBack = new Button(new Properties("Back",SCREEN_WIDTH - 100, 5, 80, 80, SDL_FLIP_NONE));
    mUpHealth = new Button(new Properties("Up",100, SCREEN_HEIGHT / 3, 80, 80, SDL_FLIP_NONE));
    mUpDamage = new Button(new Properties("Up",100, SCREEN_HEIGHT*2/3, 80, 80, SDL_FLIP_NONE));
    return true;
}

void Upgrade::Back()
{
    Game::Get_Instance()->PopState();
}

void Upgrade::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 200, 0, 0, 255);

    TextureManager::Get_Instance()->Draw("Upgrade_bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, nullptr, SDL_FLIP_NONE);

    mBack->Draw();
    mUpHealth->Draw();
    mUpDamage->Draw();
    
    TextureManager::Get_Instance()->LoadText("Price", "Price: 1000");
    TextureManager::Get_Instance()->DrawText("Price", SCREEN_WIDTH/2 - 100, 5, 0, nullptr, SDL_FLIP_NONE);
    Health::Get_Instance()->Draw_Num_Health();
    Damage::Get_Instance()->Draw_Num_Damage();
    Coin::Get_Instance()->Draw_Num_Coins();

    SDL_RenderPresent(gGS_Renderer);
}

void Upgrade::Events()
{
    if(mUpHealth->Get_Button_State() == MOUSE_DOWN and mUpHealth->Is_New_State())
    {
        gUp_Health = true;
        mUpHealth->Set_Button_State(MOUSE_OVER);
    }
    if(mUpDamage->Get_Button_State() == MOUSE_DOWN and mUpDamage->Is_New_State())
    {
        gUp_Damage = true;
        mUpDamage->Set_Button_State(MOUSE_OVER);
    }
    if((mBack->Get_Button_State() == MOUSE_DOWN) or Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_ESCAPE))
    {
        gIs_Back = true;
        mBack->Set_Button_State(MOUSE_OUT);
    }
}

void Upgrade::Update()
{
    Events();
    if(!gIs_Back)
    {
        double dt = Timer::Get_Instance()->Get_Delta_Time();

        mBack->State_Update();
        mUpHealth->State_Update();
        mUpDamage->State_Update();

        if(gUp_Health)
        {           
            Health::Get_Instance()->Up_Num_Health(1000);
            Health::Get_Instance()->Save_Num_Health();
            Health::Get_Instance()->Get_Num_Health();
            gUp_Health = false;
        }
        if(gUp_Damage)
        {
            Damage::Get_Instance()->Up_Num_Damage(10);
            Damage::Get_Instance()->Save_Num_Damage();
            Damage::Get_Instance()->Get_Num_Damage();
            gUp_Damage = false;
        }
        Health::Get_Instance()->Update(dt);
        Damage::Get_Instance()->Update(dt);
        Coin::Get_Instance()->Update(dt);
    }
    else
    {
        if(gIs_Back) 
        {
            gIs_Back = false;
            SDL_Delay(200);
            Back();
        }
    }
}

void Upgrade::Clean()
{
    delete mBack;
    delete mUpHealth;
    delete mUpDamage;
}