#include "Play.hpp"
#include "Menu.hpp"
#include "Defeat.hpp"
#include "../Game.hpp"
#include "../Entity/Characters/Warrior.hpp"
#include "../Entity/Characters/Orc.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../Inputs/Input.hpp"
#include "../Timer/Timer.hpp"
#include "../Map/Map.hpp"
#include "../Camera/Camera.hpp"
#include "../Physics/CollisionHandler.hpp"
#include "../Entity/Characters/Boss.hpp"
#include "../Entity/Coins/Coin.hpp"
#include "../Entity/ObjectHandler.hpp"
#include "../SoundManager/Sound.hpp"
#include "../WaveManager/WaveManager.hpp"

Play::Play()
{
    gPause = false;
    gIs_Defeat = false;
    gIs_Menu = false;
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    WaveManager::Get_Instance()->Reset_Waves();
    WaveManager::Get_Instance()->Update_Wave(WaveManager::Get_Instance()->Get_Current_Wave());
}

void Play::Init_Player()
{
    ObjectHandler::Get_Instance()->New_Player(100, 200);
    Camera::Get_Instance()->Set_Target(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
}
void Play::Init_Orcs()
{
    int Num = 3 + (WaveManager::Get_Instance()->Get_Current_Wave() + 1) / 5;
//    std::cout << "Num Enemy: " << Num << '\n';
    for (int i = 0; i < Num; i++)
    {
        int MAX = 1000, MIN = 600;
        int posX = rand() % (MAX - MIN + 1) + MIN;
        ObjectHandler::Get_Instance()->Add_New_Enemy(posX, 100);
    }
}
void Play::Init_Boss()
{
    int Num = (WaveManager::Get_Instance()->Get_Current_Wave() + 1) / 5;
    std::cout << "Num Boss: " << Num << '\n';
    for( int i = 0; i < Num; i++ )
    {
        int MAX = 1400, MIN = 1000;
        int posX = rand() % (MAX - MIN + 1) + MIN;

        ObjectHandler::Get_Instance()->Add_New_Boss(posX, 100);
    }
}
void Play::Init_Other()
{
    TextureManager::Get_Instance()->LoadText("Pause_ms", "PAUSE");
    Sound::Get_Instance()->PlayMusic("bg_music_playgame");

    Coin::Get_Instance()->Get_Num_Coins();

    Map::Get_Instance()->Create_White_Map();
    Map::Get_Instance()->Read_Map();    

    ObjectHandler::Get_Instance()->Add_New_Heart();
}

bool Play::Init()
{

    WaveManager::Get_Instance()->Reset_Waves();
    WaveManager::Get_Instance()->Update_Wave(WaveManager::Get_Instance()->Get_Current_Wave());
    
    if(!ObjectHandler::Get_Instance()->Is_Clear()) ObjectHandler::Get_Instance()->Delete_All();

    mPause = new Button(new Properties("Pause", SCREEN_WIDTH - 100, 5, 80, 80, SDL_FLIP_NONE));
    mMenu = new Button(new Properties("Menu",SCREEN_WIDTH / 2 - 70, 250, 141, 64, SDL_FLIP_NONE));

    Init_Other();
    Init_Player();
    Init_Orcs();
    Init_Boss();

    return true;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(gGS_Renderer, 10, 200, 10, 255);
    SDL_RenderClear(gGS_Renderer);

    TextureManager::Get_Instance()->DrawBackGround("Background", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
    Map::Get_Instance()->Draw();
    
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++) 
    ObjectHandler::Get_Instance()->Get_Boss(i)->Draw();
    for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    ObjectHandler::Get_Instance()->Get_Enemy(i)->Draw();
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Crystals(); i++)
    {
        ObjectHandler::Get_Instance()->Get_Crystal(i)->Draw();
        // std::cout << i << " Draw Crystal\n";
    }

    ObjectHandler::Get_Instance()->Get_Player()->Draw();
    ObjectHandler::Get_Instance()->Get_Heart(0)->Draw();

    if(gPause)
    {
        TextureManager::Get_Instance()->DrawBackGround("Pause_bg", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
        mMenu->Draw();
        TextureManager::Get_Instance()->DrawText("Pause_ms", SCREEN_WIDTH/2 - 55, 150, 0, nullptr, SDL_FLIP_NONE);
    }
    mPause->Draw();

    Coin::Get_Instance()->Draw_Num_Coins();

    WaveManager::Get_Instance()->Draw_Wave();

    SDL_RenderPresent(gGS_Renderer);
}

void Play::Update()
{
    Events();

//    std::cout << ObjectHandler::Get_Instance()->Get_Num_Crystals() << '\n';
    if(!gPause and !gIs_Defeat and !ObjectHandler::Get_Instance()->Is_Clear() and !gIs_Menu)
    {
        double dt = Timer::Get_Instance()->Get_Delta_Time();

        mPause->State_Update();

        int blocked_back = 0;
        int blocked_fore = 0;
        
        //boss
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++)
        {
            std::cout << ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Origin()->X << '\n';
            ObjectHandler::Get_Instance()->Get_Boss(i)->Update(dt);
            if(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Killed()) 
            {
                ObjectHandler::Get_Instance()->Delete_Boss(i);   
                i--; 
            }
        }
        //enemy
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
        {
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Update(dt);
            if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Killed()) 
            {
                ObjectHandler::Get_Instance()->Delete_Enemy(i); 
                i--;
            }
        }
        //bullet
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Crystals(); i++)
        {
//            std::cout << i << " a\n";
            ObjectHandler::Get_Instance()->Get_Crystal(i)->Update(dt);
            if(ObjectHandler::Get_Instance()->Get_Crystal(i)->Get_Bullet_Done())
            {
                ObjectHandler::Get_Instance()->Delete_Crystal(i);
                i--;
            }
        }
        //heart
        ObjectHandler::Get_Instance()->Get_Heart(0)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
        if(ObjectHandler::Get_Instance()->Get_Heart(0)->Get_Heart_State())
        {
            ObjectHandler::Get_Instance()->Get_Player()->Heal(ObjectHandler::Get_Instance()->Get_Heart(0)->Get_Num_Heal());
            Sound::Get_Instance()->PlayEffect("Upgrade");
            ObjectHandler::Get_Instance()->Get_Heart(0)->Set_Heart_State(false);
            ObjectHandler::Get_Instance()->Delete_Heart(0);
            do
            {
                ObjectHandler::Get_Instance()->Add_New_Heart();
                ObjectHandler::Get_Instance()->Get_Heart(0)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
                if(ObjectHandler::Get_Instance()->Get_Heart(0)->Get_Heart_State()) ObjectHandler::Get_Instance()->Delete_Heart(0);
                else break;
            } while (1);
        }
        ObjectHandler::Get_Instance()->Get_Heart(0)->Update(dt);

        ObjectHandler::Get_Instance()->Get_Player()->Update(dt); 
        if(ObjectHandler::Get_Instance()->Get_Player()->Is_Killed() == 1) gIs_Defeat = true; else gIs_Defeat = false;

        Camera::Get_Instance()->Update(dt);
        Coin::Get_Instance()->Update(dt);
    }
    else if (gIs_Defeat)
    {
        gIs_Defeat = false;
        OpenDefeat();
    }
    else if(ObjectHandler::Get_Instance()->Is_Clear())
    {
        SDL_Delay(200);
        ObjectHandler::Get_Instance()->Get_Player()->Reset_Position();
        WaveManager::Get_Instance()->Next_Wave();
        WaveManager::Get_Instance()->Update_Wave(WaveManager::Get_Instance()->Get_Current_Wave());                        
        Init_Orcs();
        Init_Boss();
    }
    else if(gPause)
    {
        mMenu->State_Update();
        mPause->State_Update();
    }
    if(gIs_Menu)
    {
        gIs_Menu = false;
        SDL_Delay(200);
        OpenMenu();
    }
}

void Play::Events()
{
    if(mMenu->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Menu = true;
        mMenu->Set_Button_State(MOUSE_OUT);
    }
    if(!gPause and (mPause->Get_Button_State() == MOUSE_DOWN and mPause->Is_New_State()))
    {
        gPause = true;
        mPause->Set_Props("Play");
        mPause->Set_Button_State(MOUSE_OUT);
    } 
    if(gPause and mPause->Get_Button_State() == MOUSE_DOWN and mPause->Is_New_State())
    {
        gPause = false;
        mPause->Set_Props("Pause");
        mPause->Set_Button_State(MOUSE_OUT);
    }
}

bool Play::Exit()
{
    TextureManager::Get_Instance()->Clean();

    ObjectHandler::Get_Instance()->Delete_All();
}

void Play::OpenMenu()
{
    Game::Get_Instance()->ChangeState(new Menu());
}
void Play::OpenDefeat()
{
    Game::Get_Instance()->ChangeState(new Defeat());
}

