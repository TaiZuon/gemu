#include "Coin.hpp"
#include <fstream>

Coin* Coin::g_Instance = nullptr;

void Coin::Save_Num_Coins()
{
    std::ofstream file("src/Entity/Coins/Coin.txt");
    if (!file) std::cout << "file not open to save!\n";
    file << gNum_Coins << '\n';
    file.close();
}

void Coin::Get_Num_Coins()
{
    std::ifstream file("src/Entity/Coins/Coin.txt");
    if (!file) std::cout << "file not open to get!\n";
    file >> gNum_Coins;
    file.close();
}

void Coin::Check_Num_Coins()
{
    std::cout << "Coins: " << gNum_Coins << "\n";
}