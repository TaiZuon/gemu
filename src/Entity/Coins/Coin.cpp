#include "Coin.hpp"
#include <fstream>
#include "../../TextureManager/TextureManager.hpp"
#include <string>
#include "../../Camera/Camera.hpp"

Coin* Coin::g_Instance = nullptr;

Coin::Coin()
{
    gAnimation = new Animation();
    gAnimation->Set_Props("Coin", 1, 9, 50, SDL_FLIP_NONE);
}

const char* int_to_char(int x)
{
    std::string str = std::to_string(x);

    return str.c_str();
}

void Coin::Save_Num_Coins()
{
    std::ofstream file("data/Coin.txt");
    if (!file) std::cout << "file not open to save!\n";
    file << gNum_Coins << '\n';
    file.close();
}

void Coin::Get_Num_Coins()
{
    std::ifstream file("data/Coin.txt");
    if (!file) std::cout << "file not open to get!\n";
    file >> gNum_Coins;
    file.close();
}

int Coin::Check_Num_Coins()
{
    return gNum_Coins;
}

bool Coin::Is_Enough(int price)
{
    if(gNum_Coins >= price) return true;
    else return false;
}

void Coin::Draw_Num_Coins()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    gAnimation->Draw(10 + (int) Cam.X, 5 + (int) Cam.Y, 30, 30);
    int n = Coin::Get_Instance()->Check_Num_Coins();
    TextureManager::Get_Instance()->LoadText("Num_Coins", std::to_string(n));
    TextureManager::Get_Instance()->DrawText("Num_Coins", 50, 5, 0, nullptr, SDL_FLIP_NONE);
}

void Coin::Update(double dt)
{
    gAnimation->Set_Props("Coin", 1, 9, 50, SDL_FLIP_NONE);
    bool reset = true;
    bool repeat = true;
    gAnimation->Update(dt, repeat, reset);
}