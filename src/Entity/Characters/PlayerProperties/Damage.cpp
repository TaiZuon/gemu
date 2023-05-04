#include "Damage.hpp"
#include <fstream>
#include "../../../TextureManager/TextureManager.hpp"
#include <string>
#include "../../../Camera/Camera.hpp"

Damage* Damage::g_Instance = nullptr;

Damage::Damage()
{
    gAnimation = new Animation();
    gAnimation->Set_Props("Heart", 1, 4, 200, SDL_FLIP_NONE);
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
int Damage::Check_Num_Damage()
{
    return gNum_Damage;
}
void Damage::Draw_Num_Damage()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();

    gAnimation->Draw(10 + (int) Cam.X, 5 + (int) Cam.Y, 30, 30);
    int n = Damage::Get_Instance()->Check_Num_Damage();
    TextureManager::Get_Instance()->LoadText("Num_Damage", std::to_string(n));
    TextureManager::Get_Instance()->DrawText("Num_Damage", 50, 5, 0, nullptr, SDL_FLIP_NONE);
}