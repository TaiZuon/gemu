#pragma once

#include "Item.hpp"

class Heart: public Item
{
public:
    Heart(Properties* prop);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);

    //player
    SDL_Rect gTar_Box;
    void Set_Tar_Box(SDL_Rect a);
    int Is_Tar_Colly();

    int Get_Num_Heal();

    bool Get_Heart_State()
    {
        return gIs_Touched;
    }
private:
    int gHeal = 100;
    bool gIs_Touched;
};