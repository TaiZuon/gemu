#pragma once

#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../../Inputs/Input.hpp"

class Orc: public Character{
public:
    Orc(Properties* props);

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
    void Set_Tar_Origin(Point* a)
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
    int Is_Tar_Colly()
    {
        return CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTar_Box);
    }
    int Is_Tar_Colly_Seperate()
    {
        return CollisionHandler::Get_Instance()->Is_Seperate_Collision(gCollider->Get_Box(), gTar_Box);
    }
    void Set_Tar_Dir(int a)
    {
        gTar_Dir = a;
    }
    bool Is_Taken_Dam()
    {
        if(Is_Tar_Colly() != 0)
        {
            switch (CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTar_Box))
            {
            case FORWARD:
                /* code */
                if(gTar_Dir == BACKWARD) return true;
                else return false;
                break;
            case BACKWARD:
                if(gTar_Dir == FORWARD) return true;
                else return false;
                break;
            default:
                break;
            }
        }
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
    bool Is_Killed()
    {
        return gIs_Killed;
    }
    void Hurt(int dam)
    {
        if(Is_Tar_Colly() != 0) 
        {
            gHealth -= dam;
            gHealth = std::max(gHealth, 0);
        }
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
    bool gIs_Killed;

    bool gTar_Attack;
    bool gTar_Dead;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 2.0;
    double gDead_Time = 20.0;

    int gMax_Health;
    int gMax_Damage;

    int gHealth;
    int gDamage;
    int gTar_Dam;
    int gTar_Dir;

    int gVal = 10;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};