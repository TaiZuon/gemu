#pragma once

#include "Item.hpp"
#include "../../Physics/RigidBody.hpp"

class Bullet: public Item
{
public:
    Bullet(Properties* prop);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    //player
    SDL_Rect gTar_Box;
    void Set_Tar_Box(SDL_Rect a);
    int Is_Tar_Colly();

    int Get_Dam();

    bool Get_Bullet_State()
    {
        return gIs_Done;
    }
    void Set_Bullet_State(bool a)
    {
        gIs_Touched = a;
    }
    void Set_Dir(int a)
    {
        gDir = a;
    }
private:
    int gDam = 100;
    int gDir;
    int gTime_Start;

    bool gIs_Touched;
    bool gIs_Done;

    double gEx_Time = 20.0;

    RigidBody* gRigidBody;
};