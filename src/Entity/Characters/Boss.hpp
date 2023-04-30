#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
#include "../../Physics/CollisionHandler.hpp"

class Boss: public Character{
public:
    Boss(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    void Draw_Health();
    RigidBody* Get_RigidBody()
    {
        return gRigidBody;
    }
    Point* gTar;
    SDL_Rect gTar_Box;
    void Set_Tar(Point* a)
    {
        gTar = a;
    }
    void Set_Tar_Box(SDL_Rect t)
    {
        gTar_Box = t;
    }
    void Set_Tar_State(bool attack, bool dead)
    {
        gTar_Attack = attack;
        gTar_Dead = dead;
    }
    void Set_Tar_Dam(int a)
    {
        gTar_Dam = a;
    }
    bool Is_Tar_Colly()
    {
        if(CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTar_Box))
        return true;
        else
        return false;
    }
    void Up_Dam(int dtDam)
    {
        gDamage += dtDam;
    }
    int Get_Damage()
    {
        return gDamage;
    }
    bool Is_Attacking()
    {
        return gIs_Attacking;
    }
    bool Is_Dead()
    {
        return gIs_Dead;
    }
    void Hurt(int dam)
    {
        if(Is_Tar_Colly()) gHealth -= dam;
    }
    void Dead()
    {
        gIs_Jumping = false;
        gIs_Falling = false;
        gIs_Running = false;
        gIs_Attacking = false;
        gIs_Landed = false; 
        gIs_Hurt = false;
    }

private:
    bool gIs_Jumping;
    bool gIs_Falling;
    bool gIs_Running;
    bool gIs_Attacking;
    bool gIs_Landed;
    bool gIs_Hurt;
    bool gIs_Dead;

    bool gTar_Attack;
    bool gTar_Dead;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 2.0;
    double gDead_Time = 2.0;

    int gHealth = 2500;
    int gDamage = 1;
    int gTar_Dam;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};