#include "ObjectHandler.hpp"
#include "../Camera/Camera.hpp"

ObjectHandler* ObjectHandler::g_Instance = nullptr;

void ObjectHandler::New_Player(int x, int y)
{
    Player = new Warrior(new Properties("Warrior_Idle", x, y, CHAR_SIZE, CHAR_SIZE, SDL_FLIP_NONE));
}
void ObjectHandler::Add_New_Enemy(int x, int y)
{
    Orc* tEnemy = new Orc(new Properties("Orc_Idle", x, y, CHAR_SIZE, CHAR_SIZE, SDL_FLIP_NONE));
    Enemies.push_back(tEnemy);
    Num_Enemies++;
}
void ObjectHandler::Add_New_Boss(int x, int y)
{
    Boss* Bosut = new Boss(new Properties("Orc_Warrior_Idle", x, y, BOSS_SIZE, BOSS_SIZE, SDL_FLIP_NONE)); 
    Bosses.push_back(Bosut);

    Num_Bosses++;
    // std::cout << "Pos x: " << Bosses[Num_Bosses - 1]->Get_Origin()->X << '\n';
    // std::cout << "Num B: " << Bosses.size() << "\n";
}
void ObjectHandler::Add_New_Crystal(int x, int y, int dir, int dam)
{
    Num_Crystals++;
    Bullet* Crysta;
//    std::cout << "a" << '\n';
    Crysta = new Bullet(new Properties("Bullet_Move", x, 288 + 73, 150, 120, SDL_FLIP_NONE));
    Crysta->Set_Dir(dir);
    Crysta->Set_Dam(dam);
    Crystals.push_back(Crysta);
//    std::cout << Num_Crystals << "New Crystal\n";
}
void ObjectHandler::Add_New_Heart()
{   
    int MIN_X, MAX_X;
    SDL_Rect viewbox = Camera::Get_Instance()->Get_View_Box();
    MIN_X = viewbox.x;
    MAX_X = viewbox.x + viewbox.w - HEART_SIZE;
    int MIN_Y = 350, MAX_Y = 420;
    int Pos_X = rand() % (MAX_X - MIN_X + 1) + MIN_X;
    int Pos_Y = rand() % (MAX_Y - MIN_Y + 1) + MIN_Y;
    
    H = new Heart(new Properties("Heart", Pos_X, Pos_Y, HEART_SIZE, HEART_SIZE, SDL_FLIP_NONE));
    Hearts.push_back(H);
    Num_Hearts++;

}
void ObjectHandler::Delete_Player()
{
    Player = nullptr;
}
void ObjectHandler::Delete_Enemy(int i)
{
    delete Enemies[i];
//    Enemies[i] = nullptr;
    Enemies.erase(Enemies.begin() + i);
    Num_Enemies--;
}
void ObjectHandler::Delete_Boss(int i)
{
    std::cout << "del\n";
    delete Bosses[i];
//    Bosses[i] = nullptr;
    Bosses.erase(Bosses.begin() + i);
    Num_Bosses--;
}
void ObjectHandler::Delete_Crystal(int i)
{
    delete Crystals[i];
    Crystals.erase(Crystals.begin() + i);
    Num_Crystals--;
//    std::cout << i << "Delete Crystal!\n";

}
void ObjectHandler::Delete_Heart(int i)
{
    Hearts.erase(Hearts.begin() + i);
    Num_Hearts--;
}
bool ObjectHandler::Is_Clear()
{
    if(Get_Num_Bosses() == 0 and Get_Num_Enemies() == 0) return true;
    else return false; 
}
void ObjectHandler::Delete_All()
{
    while(Num_Enemies)
    {
        Delete_Enemy(0);
    }
    while(Num_Bosses)
    {
        Delete_Boss(0);
    }
    while (Num_Hearts)
    {
        Delete_Heart(0);
    } 
    while (Num_Crystals)
    {
        Delete_Crystal(0);
    }
}

