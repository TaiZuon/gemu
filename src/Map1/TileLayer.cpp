#include "TileLayer.hpp"

TileLayer::TileLayer(int Tile_size, int Row_count, int Col_count, Tile_Map Tile_map, Tile_Set_List Tile_sets)
{
    gTile_Size = Tile_size;
    gRow_Count = Row_count;
    gCol_Count = Col_count;
    gTile_Map = Tile_map;
    gTile_Sets = Tile_sets;
}

void TileLayer::Render()
{

}

void TileLayer::Update()
{

}