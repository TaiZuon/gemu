#include "Damage.hpp"
#include <fstream>
#include "../../../TextureManager/TextureManager.hpp"
#include <string>
#include "../../../Camera/Camera.hpp"
#include "../../Coins/Coin.hpp"

Damage* Damage::g_Instance = nullptr;

Damage::Damage()
{
    gAnimation = new Animation();
    gAnimation->Set_Props("Sword", 1, 2, 400, SDL_FLIP_NONE);
}

void Damage::Update(double dt)
{
    gAnimation->Set_Props("Sword", 1, 2, 400, SDL_FLIP_NONE);
    bool reset = true;
    bool repeat = true;
    gAnimation->Update(dt, repeat, reset);
}

void Damage::Save_Num_Damage()
{
    std::ofstream file("src/Entity/Characters/PlayerProperties/Damage.txt");
    if (!file) std::cout << "file not open to save!\n";
    file << gNum_Damage << '\n';
    file.close();
}
void Damage::Get_Num_Damage()
{
    std::ifstream file("src/Entity/Characters/PlayerProperties/Damage.txt");
    if (!file) std::cout << "file not open to get!\n";
    file >> gNum_Damage;
    file.close();
}

void Damage::Up_Num_Damage(int a)
{
    if(Coin::Get_Instance()->Is_Enough(gPrice))
    {
        gNum_Damage += a;
        Coin::Get_Instance()->Up_Num_Coins(- gPrice);
    }
}

int Damage::Check_Num_Damage()
{
    return gNum_Damage;
}
void Damage::Draw_Num_Damage()
{
//    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    gAnimation->Draw(200, SCREEN_HEIGHT*2/3, HEART_SIZE, HEART_SIZE);
    int n = Damage::Get_Instance()->Check_Num_Damage();
    TextureManager::Get_Instance()->LoadText("Num_Damage", std::to_string(n));
    TextureManager::Get_Instance()->DrawText("Num_Damage", 300, SCREEN_HEIGHT*2/3 + 25, 0, nullptr, SDL_FLIP_NONE);
}