#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
#include "Orc.hpp"
#include "Boss.hpp"
#include "PlayerProperties/Damage.hpp"
#include "PlayerProperties/Health.hpp"
#include <vector>

class Warrior : public Character{
public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);

    int Get_Health();
    void Hurt(int dam);
    void Dead()
    {
        gIs_Jumping = false;
        gIs_Running = false;
        gIs_Attacking = false;
        gIs_Landed = false; 
        gIs_Hurt = false;
    }
    void Heal(int a);
    void Draw_Health();
    //enemy
    SDL_Rect gEnemy_Box;
    void Up_Enemy_Dam(int dtDam)
    {
        if(!gEnemy_Dead) gEnemy_Dam += dtDam;
    } 
    void Set_Enemy_Box(SDL_Rect a)
    {
        gEnemy_Box = a;
    }

    bool gEnemy_Attack;
    bool gEnemy_Dead;
    int gEnemy_Dam;

    void Set_Enemy_State(bool attack, bool dead)
    {
        gEnemy_Attack = attack;
        gEnemy_Dead = dead;
//        std::cout << gEnemy_Attack;
    }
    void Set_Enemy_Dam(int a)
    {
        gEnemy_Dam = a;
    }
    int Get_Damage()
    {
        return gDamage;
    }
    int Get_Dir()
    {
        if(gFlip == SDL_FLIP_NONE) return FORWARD;
        if(gFlip == SDL_FLIP_HORIZONTAL) return BACKWARD;
    }
    bool Is_Attacking()
    {
        return gIs_Attacking;
    }
    bool Is_Dead()
    {
        return gIs_Dead;
    }
    int Is_Killed()
    {
        if(gIs_Killed) return 1;
        else return 0;
    }
    void Reset_Position();
    RigidBody* Get_RigidBody()
    {
        return gRigidBody;
    }
    Collider* Get_Collider()
    {
        return gCollider;
    }
    void Block_Forward()
    {
        gIs_Blocked = FORWARD;
    }
    void Block_Backward()
    {
        gIs_Blocked = BACKWARD;
    }
    void Un_Block()
    {
        gIs_Blocked = 0;
    }

    //item
    SDL_Rect gHeart_Box;
    void Set_Heart_Box(SDL_Rect a)
    {
        gHeart_Box = a;
    }

private:
    
    int gMax_Health;
    int gMax_Damage;

    int gHealth;
    int gDamage;

    int gDirection;
    int gIs_Blocked;

    bool gIs_Jumping;
    bool gIs_Falling;
    bool gIs_Running;
    bool gIs_Attacking;
    bool gIs_Landed;
    bool gIs_Killed;

    bool gIs_Hurt;
    bool gIs_Dead;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 1.0;
    double gDead_Time = 20.0;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};