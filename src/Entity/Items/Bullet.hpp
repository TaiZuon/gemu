#pragma once

#include "Item.hpp"
#include "../../Physics/RigidBody.hpp"
#include "Entity/Characters/Warrior.hpp"

class Bullet: public Item
{
public:
    Bullet(Properties* prop);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    int Is_Tar_Colly();
    void Explose(double dt);
    bool Get_Bullet_Done()
    {
        return gIs_Done;
    }
    void Set_Dir(int a)
    {
        gDir = a;
//        std::cout << "Direction " << gDir << "\n";
    }
    void Set_Dam(int a)
    {
        gDam = a;
//        std::cout << "Damage: " << gDam << '\n';
    }
private:
    int gDam;
    int gDir;
    Uint32 gTime_Start;

    bool gIs_Touched;
    bool gIs_Done;

    double gEx_Time = 20.0;

    Warrior* gTarget;
    RigidBody* gRigidBody;
};