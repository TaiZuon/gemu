#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../../Inputs/Input.hpp"
#include "../../WaveManager/WaveManager.hpp"
#include "Warrior.hpp"

class Orc: public Character{
public:
    Orc(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    void Draw_Health();
    RigidBody* Get_RigidBody();
    Collider* Get_Collider();

    int Is_Tar_Colly();
    void Track_Tar();
    void Attack();
    void Friction();
    bool Is_Taken_Dam();
    int Get_Damage();
    bool Is_Attacking();
    bool Is_Dead();
    bool Is_Killed();
    void Hurt(int dam);
    void Dead();

private:
    bool gIs_Jumping;
    bool gIs_Falling;
    bool gIs_Running;
    bool gIs_Attacking;
    bool gIs_Landed;
    bool gIs_Hurt;
    bool gIs_Dead;
    bool gIs_Killed;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 2.0;
    double gDead_Time = 20.0;

    int gMax_Health;
    int gMax_Damage;

    int gHealth;
    int gDamage;

    int gVal = 10;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

    Warrior* gTarget = nullptr;
};