#include "Boss.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../Coins/Coin.hpp"
#include "Entity/ObjectHandler.hpp"


Boss::Boss(Properties* props): Character(props)
{
    gMax_Damage = WaveManager::Get_Instance()->Get_Boss_Damage();
    gMax_Health = WaveManager::Get_Instance()->Get_Boss_Health();

    gDamage = gMax_Damage;
    gHealth = gMax_Health;

    gTarget = ObjectHandler::Get_Instance()->Get_Player();

    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;
    gIs_Landed = false;
    gIs_Hurt = false;
    gIs_Dead = false;
    gIs_Insane = false;
    gIs_Shooting = false;
    gLast_Insane = false;
    gIs_Killed = false;

    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(-70,-120,140,120);
    gCollider->Set_Box(gTransform->X, gTransform->Y, BOSS_SIZE, BOSS_SIZE);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 5, 150, SDL_FLIP_NONE);

    // Crystal = nullptr;
}
RigidBody* Boss::Get_RigidBody()
{
    return gRigidBody;
}
Collider* Boss::Get_Collider()
{
    return gCollider;
}

void Boss::Track_Tar(double dt)
{
    if(Is_Tar_Colly() != 0)
    {
        Mele(dt);
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
            gDir = FORWARD;
            gRigidBody->Apply_ForceX(gDir * RUN_FORCES[gType]);
        }
        else 
        {
            gFlip = SDL_FLIP_HORIZONTAL;
            gDir = BACKWARD;
            gRigidBody->Apply_ForceX(gDir * RUN_FORCES[gType]);
        }   
    }
    else 
    {
        gRigidBody->Unset_Force();
        gIs_Running = false;
    }
    if(gIs_Running)
    {
        gAnimation->Set_Props("Orc_Warrior_Run", 1, 6, 100, gFlip);
    }
}
void Boss::Track_Tar_Shoot(double dt)
{
    if(Tar_In_Range()) 
    {
        Shoot(dt);
    }
    else
    {
        gIs_Shooting = false;
        gIs_Running = true;
    }
    if(std::abs(gOrigin->X - gTarget->Get_Origin()->X) > gShoot_Range)
    {
        gIs_Running = true;
    }
    else gIs_Running = false;
    if(!gIs_Attacking)
    {
        if(gTarget->Get_Origin()->X > gOrigin->X) 
        {
            gFlip = SDL_FLIP_NONE;
            gDir = FORWARD;
        }
        else 
        {
            gFlip = SDL_FLIP_HORIZONTAL;
            gDir = BACKWARD;
        }
    }
    if(gIs_Running)
    {
        gRigidBody->Apply_ForceX(gDir * RUN_FORCES[gType]);
        gAnimation->Set_Props("Orc_Warrior_Run", 1, 6, 100, gFlip);
    }
    else
    {
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
    }
}
void Boss::Hurt(int dam)
{
    if(Is_Tar_Colly()) 
    {
        gHealth -= dam;
        gHealth = std::max(gHealth, 0);
    }
}
void Boss::Is_Insane()
{
    if(float(gHealth*1.0 / gMax_Health) < 0.5) gIs_Insane = true;
    if(gLast_Insane != gIs_Insane) Sound::Get_Instance()->PlayEffect("Orc_Insane");
    else gIs_Insane = false;
    gLast_Insane = gIs_Insane;
}
void Boss::Dead()
{
    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;
    gIs_Landed = false; 
    gIs_Hurt = false;
}
void Boss::Friction()
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
void Boss::Shoot(double dt)
{
//    std::cout << gAnimation->Is_New_Frame() <<"\n";
    if(!gIs_Shooting) gAnimation->AnimationStart();
    gIs_Shooting = true;
    gRigidBody->Unset_Force();
    gAnimation->Set_Props("Orc_Warrior_Attack_2", 1, 4, 250, gFlip);
    // if(Crystal == nullptr) 
    // {
    //     Crystal = new Bullet(new Properties("Bullet_Move", gTransform->X, 288 + 73, 150, 120, gFlip));
    //     Crystal->Set_Dam(gDamage);
    //     Crystal->Set_Dir(gDir);
    // }
    if(gAnimation->Get_Frame() == 3 and gAnimation->Is_New_Frame()) ObjectHandler::Get_Instance()->Add_New_Crystal(gTransform->X, 288 + 73, gDir, gDamage);
}

void Boss::Mele(double dt)
{
    gCollider->Set_Empty(-65,-120,130,120);
    gRigidBody->Stop_Vel_X();
    if(!gIs_Attacking) gAnimation->AnimationStart();
    gIs_Attacking = true;
    gRigidBody->Unset_Force();
    gAnimation->Set_Props("Orc_Warrior_Attack_1", 1, 4, 150, gFlip);
    if(gAnimation->Get_Frame() >= 3 and gAnimation->Is_New_Frame())
    {
        Sound::Get_Instance()->PlayEffect("Orc_Attack");
        gTarget->Take_Dam(gDamage);
    }
}

int Boss::Is_Tar_Colly()
{
    return CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTarget->Get_Collider()->Get_Box());
}
int Boss::Get_Damage()
{
    return gDamage;
}

bool Boss::Is_Taken_Dam()
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
bool Boss::Is_Attacking()
{
    return gIs_Attacking;
}
bool Boss::Is_Dead()
{
    return gIs_Dead;
}
bool Boss::Is_Killed()
{
    return gIs_Killed;
}
bool Boss::Tar_In_Range()
{
    if(std::abs(gTarget->Get_Origin()->X - gOrigin->X) <= gShoot_Range) return true;
    return false;
}


void Boss::Update(double dt)
{
    bool Reset = false;
    bool Repeat = true;
    gCollider->Set_Empty(-70,-120,140,120);
    if(!gIs_Dead and !gTarget->Is_Dead())
    {
        if(gHealth <= 0)
        {
            gIs_Dead = true;
        }
        else 
        {
            gIs_Dead = false;
        }
        if(!gIs_Insane)
        {
            gType = BOSS;
            Track_Tar_Shoot(dt);
            Is_Insane();
        }
        else 
        { 
            gType = BOSS_INSANE;
            gIs_Shooting = false;
            Track_Tar(dt);
        }
        
    }
    else if(gIs_Dead)
    {
        if(gDead_Time > 0)
        {
            gDead_Time -= dt;
            if(gDead_Time <= dt)
            { 
                gIs_Killed = true;
                Coin::Get_Instance()->Up_Num_Coins(gVal);
                Sound::Get_Instance()->PlayEffect("Orc_Die");
            } else gIs_Killed = false;
        }
        gAnimation->Set_Props("Orc_Warrior_Dead", 1, 4, 100, gFlip);
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gRigidBody->Stop_Vel_Y();
        Dead();
    }
    else if(gTarget->Is_Dead())
    {
        gAnimation->Set_Props(gTexture_ID, 1, 5, 150, gFlip);
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gRigidBody->Stop_Vel_Y();
    }
    // bullet
    // if(Crystal != nullptr) 
    // {
    //     Crystal->Update(dt);
    //     if(Crystal->Get_Bullet_Done())
    //     {
    //         delete Crystal;
    //         Crystal = nullptr;
    //         std::cout << "delete Bullet!\n";
    //     }
    // }
    gRigidBody->Update(dt, gType);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, BOSS_SIZE, BOSS_SIZE);
    gRigidBody->Update(dt, gType);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    gCollider->Set_Box(gTransform->X, gTransform->Y, BOSS_SIZE, BOSS_SIZE);

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

void Boss::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
    // if(Crystal != nullptr) Crystal->Draw();

    Draw_Health();
}

void Boss::Draw_Health()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = {(int)gTransform->X + 60, (int)gTransform->Y + 50, 75, 4};
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    SDL_Rect H = Box;
    H.w = double(gHealth*1.0 / gMax_Health) *75;
    Box.x--;
    Box.y-=2;
    Box.h += 4;
    Box.w++;

    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 255, 255, 0); 
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    if(gIs_Insane) 
    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 100, 0, 0, 0); 
    else
    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 40, 40, 0); 
    SDL_RenderFillRect(Game::Get_Instance()->gRenderer, &H); 
}
 void Boss::Clean()
 {
    TextureManager::Get_Instance()->Drop(gTexture_ID);
    // if(Crystal != nullptr) Crystal->Clean();
 }