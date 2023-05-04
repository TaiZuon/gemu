#include "Health.hpp"
#include <fstream>
#include "../../../TextureManager/TextureManager.hpp"
#include <string>
#include "../../../Camera/Camera.hpp"

Health* Health::g_Instance = nullptr;

Health::Health()
{
    gAnimation = new Animation();
    gAnimation->Set_Props("Heart", 1, 4, 200, SDL_FLIP_NONE);
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

    gAnimation->Draw(10 + (int) Cam.X, 5 + (int) Cam.Y, 30, 30);
    int n = Health::Get_Instance()->Check_Num_Health();
    TextureManager::Get_Instance()->LoadText("Num_Health", std::to_string(n));
    TextureManager::Get_Instance()->DrawText("Num_Health", 50, 5, 0, nullptr, SDL_FLIP_NONE);
}