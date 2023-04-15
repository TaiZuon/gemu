#include "Layer.hpp"
#include <vector>

class GameMap
{
private:
    std::vector<Layer*> gMap_Layers;
public:
    void Render()
    {
        for(int i = 0; i < gMap_Layers.size(); i++)
            gMap_Layers[i]->Render();
    }
    void Update()
    {
        for(int i = 0; i < gMap_Layers.size(); i++)
            gMap_Layers[i]->Update();
    }
    std::vector<Layer*> Get_Map_Layers()
    {
        return gMap_Layers;
    }

};


