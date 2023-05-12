#include "Orc.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../Coins/Coin.hpp"
#include "../../SoundManager/Sound.hpp"
#include "Entity/ObjectHandler.hpp"

Orc::Orc(Properties* props): Character(props)
{
    gTarget = ObjectHandler::Get_Instance()->Get_Player();
    gMax_Damage = WaveManager::Get_Instance()->Get_Orc_Damage();
    gMax_Health = WaveManager::Get_Instance()->Get_Orc_Health();

    gDamage = gMax_Damage;
    gHealth = gMax_Health;

    gIs_Reset_Ani = true;
    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;
    gIs_Landed = false;
    gIs_Hurt = false;
    gIs_Dead = false;
    gIs_Killed = false;

    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(-35,-50,70,50);
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 5, 50, SDL_FLIP_NONE);
}
RigidBody* Orc::Get_RigidBody()
{
    return gRigidBody;
}
Collider* Orc::Get_Collider()
{
    return gCollider;
}

int Orc::Is_Tar_Colly()
{
    return CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTarget->Get_Collider()->Get_Box());
}
int Orc::Get_Damage()
{
    return gDamage;
}
bool Orc::Is_Taken_Dam()
{
    if(Is_Tar_Colly() != 0)
    {
        switch (CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTarget->Get_Collider()->Get_Box()))
        {
        case FORWARD:
            if(gTarget->Get_Dir() == BACKWARD) return true;
            else return false;
            break;
        case BACKWARD:
            if(gTarget->Get_Dir() == FORWARD) return true;
            else return false;
            break;
        default:
            break;
        }
    }
    return false;
}    
bool Orc::Is_Attacking()
{
    return gIs_Attacking;
}
bool Orc::Is_Dead()
{
    return gIs_Dead;
}
bool Orc::Is_Killed()
{
    return gIs_Killed;
}

void Orc::Hurt(int dam)
{
    if(Is_Tar_Colly() != 0) 
    {
        gHealth -= dam;
        gHealth = std::max(gHealth, 0);
    }
}
void Orc::Dead(double dt)
{
    if(gIs_Reset_Ani) 
    {
        gAnimation->AnimationStart();
        gIs_Reset_Ani = false;;
    }
    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;
    gIs_Landed = false; 
    gIs_Hurt = false;
    if(gDead_Time > 0)
    {
        gDead_Time -= dt;
    }
    else
    { 
        if(gAnimation->Get_Frame() >= 3) 
        {
            Sound::Get_Instance()->PlayEffect("Orc_Die");
            Coin::Get_Instance()->Up_Num_Coins(gVal);
            gIs_Killed = true;
        }
    }
    gAnimation->Set_Props("Orc_Dead", 1, 4, 250, gFlip);
    gRigidBody->Unset_Force();
    gRigidBody->Stop_Vel_X();
    gRigidBody->Stop_Vel_Y();

}

void Orc::Track_Tar()
{
    if(std::abs(gOrigin->X - gTarget->Get_Origin()->X) > 50 )
    {
        gIs_Running = true;
    }
    if(Is_Tar_Colly() != 0)
    {
        Attack();
        gIs_Running = false;
    }
    else
    {
        gIs_Running = true;
        gIs_Attacking = false;
    }
    if(std::abs(gOrigin->X - gTarget->Get_Origin()->X) > 5 and gIs_Running)
    {
        if(gTarget->Get_Origin()->X > gOrigin->X) 
        {
            gFlip = SDL_FLIP_NONE;
            gRigidBody->Apply_ForceX(RUN_FORCES[ORC]);
        }
        else 
        {
            gFlip = SDL_FLIP_HORIZONTAL;
            gRigidBody->Apply_ForceX(-RUN_FORCES[ORC]);
        }
    }
    else 
    {
        gRigidBody->Unset_Force();
        gIs_Running = false;
    }
    if(gIs_Running)
    {
        gAnimation->Set_Props("Orc_Run", 1, 6, 100, gFlip);
    }

} 
void Orc::Attack()
{  
    gCollider->Set_Empty(-30,-50,60,50);
    gRigidBody->Stop_Vel_X();
    if(!gIs_Attacking) gAnimation->AnimationStart();
    gIs_Attacking = true;
    gRigidBody->Unset_Force();
    gAnimation->Set_Props("Orc_Attack_1", 1, 4, 150, gFlip);
    if(gAnimation->Get_Frame() >= 2 and gAnimation->Is_New_Frame())
    {
        Sound::Get_Instance()->PlayEffect("Orc_Attack");
        gTarget->Take_Dam(gDamage);
    }
}

void Orc::Friction()
{
    if(std::abs(gRigidBody->Get_Velocity().X) != 0)
    {
        double v_temp = gRigidBody->Get_Velocity().X;
        Vector2D friction(-FRICTION * (v_temp/std::abs(v_temp)), 0);
        gRigidBody->Apply_Friction(friction);
    } 
    else
    {
        gRigidBody->Unset_Friction();
    }
}
void Orc::Update(double dt)
{
    bool Reset = false;
    bool Repeat = false;
    gCollider->Set_Empty(-35,-50,70,50);
    if(!gIs_Dead and !gTarget->Is_Dead())
    {
        Friction();
        if(gHealth == 0)
        {
            gIs_Dead = true;
        }
        else 
        {
            gIs_Dead = false;
        }
        Track_Tar();
    }
    else if(gTarget->Is_Dead())
    {
        gAnimation->Set_Props(gTexture_ID, 1, 5, 150, gFlip);
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gRigidBody->Stop_Vel_Y();
        Repeat = true;
    } 
    else 
    {
        Dead(dt);
    } 

    gRigidBody->Update(dt, ORC);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);
    gRigidBody->Update(dt, ORC);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);

    SDL_Rect Box = gCollider->Get_Box();
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);

    if(CollisionHandler::Get_Instance()->Is_Map_Collision(gCollider->Get_Box()))
    {
        gIs_Landed = true;
        gTransform->Y = gLast_Safe_Position.Y;
        gRigidBody->Stop_Vel_Y();
    }
    else
    {
        gIs_Landed = false;
    }

    gOrigin->X = gTransform->X + gWidth/2;
    gOrigin->Y = gTransform->Y + gHeight/2;

    gAnimation->Update(dt, Repeat, Reset);
}

void Orc::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
    Draw_Health();
}

void Orc::Draw_Health()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = {(int)gTransform->X + 36, (int)gTransform->Y + 30, 25, 4};
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    SDL_Rect H = Box;
    H.w = double(gHealth*1.0 / gMax_Health) *25;
    Box.x--;
    Box.y-=2;
    Box.h += 4;
    Box.w++;

    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 255, 255, 0); 
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 50, 50, 0); 
    SDL_RenderFillRect(Game::Get_Instance()->gRenderer, &H); 
}

void Orc::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}