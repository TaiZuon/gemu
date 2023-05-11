#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
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

    void Friction();
    void Fall();
    void Run();
    void Idle();
    void Jump(double dt);
    void Attack();
    void Hurt(double dt);
    void Dead();
    void Heal(int a);
    void Draw_Health();

    bool gEnemy_Attack;
    bool gEnemy_Dead;

    
    void Set_Enemy_State(bool attack, bool dead)
    {
        gEnemy_Attack = attack;
        gEnemy_Dead = dead;
//        std::cout << gEnemy_Attack;
    }
    
    void Take_Dam(int dam);
    int Get_Damage();
    int Get_Dir();
    bool Is_Attacking();
    bool Is_Dead();
    int Is_Killed();
    void Reset_Position();
    RigidBody* Get_RigidBody()
    {
        return gRigidBody;
    }
    Collider* Get_Collider()
    {
        return gCollider;
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
    double gHurt_Time = 0.2;
    double gDead_Time = 20.0;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};