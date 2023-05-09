#include "Health.hpp"
#include <fstream>
#include "../../../TextureManager/TextureManager.hpp"
#include <string>
#include "../../../Camera/Camera.hpp"
#include "../../Coins/Coin.hpp"
#include "../../../SoundManager/Sound.hpp"

Health* Health::g_Instance = nullptr;

Health::Health()
{
    gAnimation = new Animation();
    gAnimation->Set_Props("Heart", 1, 4, 200, SDL_FLIP_NONE);
}

void Health::Up_Num_Health(int a)
{
    if(Coin::Get_Instance()->Is_Enough(gPrice))
    {
        gNum_Health += a;
        Coin::Get_Instance()->Up_Num_Coins(- gPrice);
        Sound::Get_Instance()->PlayEffect("Upgrade");
    }
    else
    {
        Sound::Get_Instance()->PlayEffect("Invalid");
    }
}

void Health::Update(double dt)
{
    gAnimation->Set_Props("Heart", 1, 4, 200, SDL_FLIP_NONE);
    bool reset = true;
    bool repeat = true;
    gAnimation->Update(dt, repeat, reset);
}

void Health::Save_Num_Health()
{
    std::ofstream file("src/Entity/Characters/PlayerProperties/Health.txt");
    if (!file) std::cout << "file not open to save!\n";
    file << gNum_Health << '\n';
    file.close();
}
void Health::Get_Num_Health()
{
    std::ifstream file("src/Entity/Characters/PlayerProperties/Health.txt");
    if (!file) std::cout << "file not open to get!\n";
    file >> gNum_Health;
    file.close();
}
int Health::Check_Num_Health()
{
    return gNum_Health;
}
void Health::Draw_Num_Health()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    gAnimation->Draw(200 + (int) Cam.X, SCREEN_HEIGHT / 3 + (int) Cam.Y, HEART_SIZE, HEART_SIZE);
    int n = Health::Get_Instance()->Check_Num_Health();
    TextureManager::Get_Instance()->LoadText("Num_Health", std::to_string(n));
    TextureManager::Get_Instance()->DrawText("Num_Health", 300, SCREEN_HEIGHT / 3 + 25, 0, nullptr, SDL_FLIP_NONE);
}