#include "ObjectHandler.hpp"
#include "../Camera/Camera.hpp"

ObjectHandler* ObjectHandler::g_Instance = nullptr;

void ObjectHandler::New_Player(int x, int y)
{
    Player = new Warrior(new Properties("Warrior_Idle", x, y, CHAR_SIZE, CHAR_SIZE, SDL_FLIP_NONE));
    std::cout << "In ObjHDL, Player die? : " << Player->Is_Killed() << "\n";
}
void ObjectHandler::Add_New_Enemy(int x, int y)
{
    Enemy = new Orc(new Properties("Orc_Idle", x, y, CHAR_SIZE, CHAR_SIZE, SDL_FLIP_NONE));
    Enemies.push_back(Enemy);
    Num_Enemies++;
}
void ObjectHandler::Add_New_Boss(int x, int y)
{
    Bosu = new Boss(new Properties("Orc_Warrior_Idle", x, y, BOSS_SIZE, BOSS_SIZE, SDL_FLIP_NONE)); 
    Bosses.push_back(Bosu);
    Num_Bosses++;
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
    Enemies[i] = nullptr;
    Enemies.erase(Enemies.begin() + i);
    Num_Enemies--;
}
void ObjectHandler::Delete_Boss(int i)
{
    Bosses[i] = nullptr;
    Bosses.erase(Bosses.begin() + i);
    Num_Bosses--;
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
}

