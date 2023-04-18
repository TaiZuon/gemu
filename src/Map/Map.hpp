#pragma once

#include "SDL.h"

const int MAP_ROWS = 20;
const int MAP_COLS = 100;

class Map
{
private:
    static Map* g_Instance;

public:
    Map(){}
    int ID_GROUND = 15;
    int ID;
    int gTile_Width = 32;
    int gTile_Height = 32;
    int gMap[MAP_ROWS][MAP_COLS];
    static Map* Get_Instance() 
    {
        return g_Instance = (g_Instance != nullptr)? g_Instance : new Map();
    }
    void Create_White_Map();
    void Read_Map();
    void Update();
    void Draw();
    void Print_MapMatrix();

};

