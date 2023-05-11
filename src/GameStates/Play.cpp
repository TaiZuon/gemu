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
    gIs_Setting = false;
    gIs_Defeat = false;
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
    int Num = 3;
    srand(time(0));
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
    for( int i = 0; i < Num; i++ )
    {
        int MAX = 1500, MIN = 1000;
        int posX = rand() % (MAX - MIN + 1) + MIN;
        ObjectHandler::Get_Instance()->Add_New_Boss(posX, 200);
    }
}
void Play::Init_Other()
{
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

    mSetting = new Button(new Properties("Back", SCREEN_WIDTH - 100, 5, 80, 80, SDL_FLIP_NONE));

    Init_Other();
    Init_Player();
    Init_Orcs();
    Init_Boss();
    std::cout << "Play init!\n";

    std::cout << gIs_Defeat << '\n'; 
    std::cout << "Player die?: " << ObjectHandler::Get_Instance()->Get_Player()->Is_Killed() << '\n';
    int a;
//    std::cin >> a; 
    return true;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(gGS_Renderer, 10, 200, 10, 255);
    SDL_RenderClear(gGS_Renderer);

    TextureManager::Get_Instance()->DrawBackGround("Background", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
    Map::Get_Instance()->Draw();

    mSetting->Draw();

    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++) 
    ObjectHandler::Get_Instance()->Get_Boss(i)->Draw();
    for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    ObjectHandler::Get_Instance()->Get_Enemy(i)->Draw();
    ObjectHandler::Get_Instance()->Get_Player()->Draw();
    ObjectHandler::Get_Instance()->Get_Heart(0)->Draw();

    Coin::Get_Instance()->Draw_Num_Coins();

    WaveManager::Get_Instance()->Draw_Wave();

    SDL_RenderPresent(gGS_Renderer);
}

void Play::Update()
{
//    std::cout << gIs_Setting << '\n';
    Events();

    if(!gIs_Setting and !gIs_Defeat and !ObjectHandler::Get_Instance()->Is_Clear())
    {
        double dt = Timer::Get_Instance()->Get_Delta_Time();

        mSetting->State_Update();

        int blocked_back = 0;
        int blocked_fore = 0;
        
        //boss
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++)
        {
            ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_State(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Dead());
            if(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Tar_Colly() != 0)  
            {       
                if(ObjectHandler::Get_Instance()->Get_Player()->gEnemy_Attack)
                ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Damage());
                if(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Killed()) 
                {
                    ObjectHandler::Get_Instance()->Delete_Boss(i);    
                }
            }
            
            //bullet
            if(ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Crystal() != nullptr)
            {
                if(ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Crystal()->Is_Tar_Colly() != 0)
                {
                    ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Crystal()->Get_Dam());
                }
            }
        }

        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
        {
//            ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_State(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Dead());
            if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Killed()) 
            {
                ObjectHandler::Get_Instance()->Delete_Enemy(i); 
            }
        }
        //heart
        ObjectHandler::Get_Instance()->Get_Heart(0)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
        if(ObjectHandler::Get_Instance()->Get_Heart(0)->Get_Heart_State())
        {
            ObjectHandler::Get_Instance()->Get_Player()->Heal(ObjectHandler::Get_Instance()->Get_Heart(0)->Get_Num_Heal());
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
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++)
        {
            ObjectHandler::Get_Instance()->Get_Boss(i)->Update(dt);
        }
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
        {
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Update(dt);
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
        ObjectHandler::Get_Instance()->Get_Player()->Reset_Position();
        WaveManager::Get_Instance()->Next_Wave();
        WaveManager::Get_Instance()->Update_Wave(WaveManager::Get_Instance()->Get_Current_Wave());                        
        Init_Orcs();
        Init_Boss();
    }
    else if(gIs_Setting)
    {
        OpenSetting();
    }
}

void Play::Events()
{
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_M))
    {
        OpenMenu();
    }
    if(!gIs_Setting and (Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_ESCAPE) or (mSetting->Get_Button_State() == MOUSE_DOWN and mSetting->Is_New_State())))
    {
        gIs_Setting = true;
        // mSetting->Set_Button_State(MOUSE_OUT);
    } else
    if(gIs_Setting and Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_SPACE))
    {
        gIs_Setting = false;
        // mSetting->Set_Button_State(MOUSE_OUT);
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

void Play::OpenSetting()
{

}
