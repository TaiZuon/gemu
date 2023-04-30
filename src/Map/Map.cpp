#include "Map.hpp"
#include <fstream>
#include <iostream>
#include "../TextureManager/TextureManager.hpp"

Map* Map::g_Instance = nullptr; 

void Map::Create_White_Map()
{
    std::ofstream file ("src/Map/MapMatrix.txt");
    if (!file) std::cout << "file not open!\n";
    for ( int row = 0; row < MAP_ROWS; row++ )
    {
        if( row == ID_GROUND ) ID = 2; 
        else if ( row > ID_GROUND ) ID = 12;
        else ID = 0;  
        for ( int col = 0; col < MAP_COLS; col++ )
        {
            file << ID << " ";
        } 
        file << "\n";
    }
    file.close();
}

void Map::Read_Map()
{
    std::ifstream file ("src/Map/MapMatrix.txt");
    for( int row = 0; row < MAP_ROWS; row++ )
    {
        for( int col = 0; col < MAP_COLS; col++ )
        file >> gMap[row][col]; 
    }
}

void Map::Print_MapMatrix()
{
    for( int row = 0; row < MAP_ROWS; row++ )
    {
        for( int col = 0; col < MAP_COLS; col++ )
        std::cout << gMap[row][col] << " ";
        std:: cout << '\n'; 
    }
}

void Map::Draw()
{
    for( int row = 0; row < MAP_ROWS; row++ )
    {
        for( int col = 0; col < MAP_COLS; col++)
        {
            std::string Tile_ID = "Tile_";
            if(gMap[row][col]!=0)
            {
                if( gMap[row][col] < 10 ) Tile_ID += "02";
                else Tile_ID += "12"; 
//                std::cout << Tile_ID << ' ';
//                TextureManager::Get_Instance()->Draw("Tile_02", i*gTile_Width, j*gTile_Height, gTile_Width, gTile_Height, 0, NULL, SDL_FLIP_NONE);
//                std::cout << i*gTile_Width << "\n";
//                TextureManager::Get_Instance()->Draw(Tile_ID, i*gTile_Width, j*gTile_Height, gTile_Width, gTile_Height, 0, NULL, SDL_FLIP_NONE);
                TextureManager::Get_Instance()->DrawTile(Tile_ID, col * gTile_Width, row * gTile_Height, gTile_Width, 0, nullptr, SDL_FLIP_NONE);
            }
//            std::cout << std::endl;
        }
    }
}