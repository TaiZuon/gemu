#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../Items/Bullet.hpp"
#include "../../WaveManager/WaveManager.hpp"
#include "../../SoundManager/Sound.hpp"
#include "Warrior.hpp"

class Boss: public Character{
public:
    Boss(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    
    RigidBody* Get_RigidBody();
    Collider* Get_Collider();

    int Get_Damage();
    int Is_Tar_Colly();
    
    void Draw_Health();
    void Hurt(int dam);
    void Is_Insane();
    void Track_Tar(double dt);
    void Track_Tar_Shoot(double dt);
    void Dead();
    void Shoot(double dt);
    void Mele(double dt);
    void Friction();

    bool Is_Taken_Dam();
    bool Is_Attacking();
    bool Is_Dead();
    bool Is_Killed();
    bool Tar_In_Range();

    
private:
    bool gIs_Jumping;
    bool gIs_Falling;
    bool gIs_Running;
    bool gIs_Attacking;
    bool gIs_Landed;
    bool gIs_Hurt;
    bool gIs_Dead;
    bool gIs_Killed;
    bool gIs_Insane;
    bool gIs_Shooting;
    bool gLast_Insane;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 2.0;
    double gDead_Time = 20.0;
    double gShoot_Time = 5.0;

    double gShoot_Range = BOSS_RANGE;

    int gMax_Health;
    int gMax_Damage;

    int gType;
    int gHealth;
    
    int gDamage;
    int gDir;

    int gVal = 100;

    Bullet* Crystal = nullptr;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

    Warrior* gTarget = nullptr;
};