#include "ObjectHandler.hpp"

ObjectHandler* ObjectHandler::g_Instance = nullptr;

void ObjectHandler::New_Player(int x, int y)
{
    Player = new Warrior(new Properties("Warrior_Idle", x, y, CHAR_SIZE, CHAR_SIZE, SDL_FLIP_NONE));
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
void ObjectHandler::Delete_Player()
{
    delete Player;
}
void ObjectHandler::Delete_Enemy(int i)
{
    Enemies.erase(Enemies.begin() + i);
    Num_Enemies--;
}
void ObjectHandler::Delete_Boss(int i)
{
    Bosses.erase(Bosses.begin() + i);
    Num_Bosses--;
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
    Delete_Player();
}

