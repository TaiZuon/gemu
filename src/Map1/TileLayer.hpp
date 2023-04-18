#include "Layer.hpp"
#include "iostream"
#include <vector>

struct TileSet
{
    int First, LastID;
    int RoW_Count, Col_Count;
    int Tile_Count, Tile_Size;
    std::string Name;
};

using Tile_Set_List = std::vector<TileSet>;
using Tile_Map = std::vector<std::vector<TileSet>>;

class TileLayer : public Layer
{
private:
    int gTile_Size;
    int gRow_Count, gCol_Count;
    Tile_Map gTile_Map;
    Tile_Set_List gTile_Sets;

public:
    TileLayer(int Tile_size, int Row_count, int Col_count, Tile_Map Tile_map, Tile_Set_List Tile_sets);
    virtual void Render();
    virtual void Update();
    Tile_Map Get_Tile_Map() 
    {
        return gTile_Map;
    }
};


