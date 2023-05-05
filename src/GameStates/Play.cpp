#include "Play.hpp"
#include "Menu.hpp"
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

Play::Play()
{
    gIs_Setting = false;
    gGS_Renderer = Game::Get_Instance()->gRenderer;
}

bool Play::Init()
{
    int Num = 3;

    Coin::Get_Instance()->Get_Num_Coins();

    Map::Get_Instance()->Create_White_Map();
    Map::Get_Instance()->Read_Map();

//    ObjectHandler::Get_Instance()->Delete_All();

    ObjectHandler::Get_Instance()->New_Player(100, 200);

    ObjectHandler::Get_Instance()->Add_New_Boss(400, 200);

    srand(time(0));
    for (int i = 0; i < Num; i++)
    {
        int MAX = 600, MIN = 0;
        int posX = rand() % (MAX - MIN + 1) + MIN;
        ObjectHandler::Get_Instance()->Add_New_Enemy(posX, 100);
    }

    ObjectHandler::Get_Instance()->Add_New_Heart();

    Camera::Get_Instance()->Set_Target(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
    std::cout << "Play init!\n";
    return true;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(gGS_Renderer, 10, 200, 10, 255);
    SDL_RenderClear(gGS_Renderer);

    TextureManager::Get_Instance()->DrawBackGround("Background", 0, 0, 1600, 640, 0, nullptr, SDL_FLIP_NONE);
    Map::Get_Instance()->Draw();

    ObjectHandler::Get_Instance()->Get_Boss(0)->Draw();
    for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    ObjectHandler::Get_Instance()->Get_Enemy(i)->Draw();
    ObjectHandler::Get_Instance()->Get_Player()->Draw();
    ObjectHandler::Get_Instance()->Get_Heart(0)->Draw();
    Coin::Get_Instance()->Draw_Num_Coins();

    SDL_RenderPresent(gGS_Renderer);
}

void Play::Update()
{
//    std::cout << gIs_Setting << '\n';
    Events();

    if(!gIs_Setting)
    {
        double dt = Timer::Get_Instance()->Get_Delta_Time();

        int blocked_back = 0;
        int blocked_fore = 0;

        ObjectHandler::Get_Instance()->Get_Boss(0)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
        ObjectHandler::Get_Instance()->Get_Boss(0)->Set_Tar(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
        ObjectHandler::Get_Instance()->Get_Boss(0)->Set_Tar_Dir(ObjectHandler::Get_Instance()->Get_Player()->Get_Dir());
        ObjectHandler::Get_Instance()->Get_Boss(0)->Set_Tar_Dam(ObjectHandler::Get_Instance()->Get_Player()->Get_Damage());
        ObjectHandler::Get_Instance()->Get_Boss(0)->Set_Tar_State(ObjectHandler::Get_Instance()->Get_Player()->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Player()->Is_Dead());
        ObjectHandler::Get_Instance()->Get_Boss(0)->Update(dt);

        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
        {
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Dir(ObjectHandler::Get_Instance()->Get_Player()->Get_Dir());
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Box(ObjectHandler::Get_Instance()->Get_Player()->Get_Collider()->Get_Box());
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Origin(ObjectHandler::Get_Instance()->Get_Player()->Get_Origin());
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_Dam(ObjectHandler::Get_Instance()->Get_Player()->Get_Damage());
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Set_Tar_State(ObjectHandler::Get_Instance()->Get_Player()->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Player()->Is_Dead());
            ObjectHandler::Get_Instance()->Get_Enemy(i)->Update(dt);
        }
        ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_Dam(0);
        
        //boss
        ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_State(ObjectHandler::Get_Instance()->Get_Boss(0)->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Boss(0)->Is_Dead());
        if(ObjectHandler::Get_Instance()->Get_Boss(0)->Is_Tar_Colly() != 0)  
        {       
        ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_Dam(ObjectHandler::Get_Instance()->Get_Boss(0)->Get_Damage());
        
        if(ObjectHandler::Get_Instance()->Get_Player()->gEnemy_Attack)
        ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Boss(0)->Get_Damage());
        
        switch (ObjectHandler::Get_Instance()->Get_Boss(0)->Is_Tar_Colly())
        {
        case FORWARD:
            if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == BACKWARD) blocked_back--;
            break;
        case BACKWARD:
            if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == FORWARD) blocked_fore++;
            break;
            default:
                break;
            }
        }
        //
        for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
        {
//            std::cout << ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Tar_Colly() << '\n';
            ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_State(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Attacking(), ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Dead());

            if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Tar_Colly() != 0)  
            {       
                ObjectHandler::Get_Instance()->Get_Player()->Set_Enemy_Dam(ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Damage());
                ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Damage());

                switch (ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Tar_Colly())
                {
                case FORWARD:
                    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == BACKWARD) blocked_back--;
                    break;
                case BACKWARD:
                    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == FORWARD) blocked_fore++;
                    break;
                default:
                    break;
                }
            }
            if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Killed()) 
            {
                ObjectHandler::Get_Instance()->Delete_Enemy(i);    
            }
        }
        //

        //
        if(blocked_back != 0) ObjectHandler::Get_Instance()->Get_Player()->Block_Backward();
        if(blocked_fore != 0) ObjectHandler::Get_Instance()->Get_Player()->Block_Forward();

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
        if(ObjectHandler::Get_Instance()->Get_Boss(0)->Get_Crystal() != nullptr)
        {
            if(ObjectHandler::Get_Instance()->Get_Boss(0)->Get_Crystal()->Is_Tar_Colly() != 0)
            {
                ObjectHandler::Get_Instance()->Get_Player()->Hurt(ObjectHandler::Get_Instance()->Get_Boss(0)->Get_Crystal()->Get_Dam());
            }
        }

        ObjectHandler::Get_Instance()->Get_Heart(0)->Update(dt);
        ObjectHandler::Get_Instance()->Get_Player()->Update(dt); 

        Camera::Get_Instance()->Update(dt);
        Coin::Get_Instance()->Update(dt);
    }
}

void Play::Events()
{
    if(!gIs_Setting and Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_M))
    {
        OpenMenu();
    }
    if(!gIs_Setting and Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_ESCAPE))
    {
        gIs_Setting = true;
    }
    if(gIs_Setting and Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_SPACE))
    {
        gIs_Setting = false;
    }
}

bool Play::Exit()
{
    TextureManager::Get_Instance()->Clean();

    ObjectHandler::Get_Instance()->Delete_All();
}

void Play::OpenMenu()
{
    Game::Get_Instance()->ChangeState(new Menu);
}

void Play::OpenSetting()
{

}
