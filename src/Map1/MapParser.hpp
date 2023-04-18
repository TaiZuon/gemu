#include "../Vendor/Tinyxml/tinyxml.h"
#include <map>
#include <string>
#include "GameMap.hpp"
#include "TileLayer.hpp"

class MapParser
{
private:
    static MapParser* g_Instance;
    std::map<std::string, GameMap> gMaps;
public:
    MapParser();
    static MapParser* Get_Instance()
    {
        return g_Instance = (g_Instance == nullptr)? g_Instance : new MapParser();
    }
    void Load();
    void Clean();
    GameMap* Get_Maps();
};



