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

    if(gTarget == nullptr)
    {
        gTarget = ObjectHandler::Get_Instance()->Get_Player();
    }

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

    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(-70,-120,140,120);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 5, 150, SDL_FLIP_NONE);
}
RigidBody* Boss::Get_RigidBody()
{
    return gRigidBody;
}
Collider* Boss::Get_Collider()
{
    return gCollider;
}
Bullet* Boss::Get_Crystal()
{
    return Crystal;
}

void Boss::Track_Tar()
{
    if(std::abs(gOrigin->X - gTarget->Get_Origin()->X) > 50 )
    {
//        std::cout << "Chase!\n";
        gIs_Running = true;
    }
    //tracking player
    if(std::abs(gOrigin->X - gTarget->Get_Origin()->X) > 5 and !gIs_Attacking)
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
        gRigidBody->Apply_ForceX(gDir * RUN_FORCES[gType]);
    }
    else 
    {
//        std::cout << "Stop!\n";
        gRigidBody->Unset_Force();
        gIs_Running = false;
    }
}
void Boss::Track_Tar_Shoot()
{
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
        gRigidBody->Apply_ForceX(gDir * RUN_FORCES[BOSS]);
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
    if(gLast_Insane != gIs_Insane) Sound::Get_Instance()->PlayEffect("Orc_Insane");
    if(float(gHealth*1.0 / gMax_Health) < 0.5) gIs_Insane = true;
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
//    std::cout << gType << '\n';
    bool Reset = false;
    bool Repeat = true;
    if(!gIs_Dead and !gTarget->Is_Dead() and !gIs_Killed)
    {
        if(!gIs_Insane)
        {
            gType = BOSS;
            Track_Tar_Shoot();
            //shoot bullet
            if(Tar_In_Range()) 
            {
                gIs_Shooting = true;
            }
            else gIs_Shooting = false;
            if(gIs_Shooting and gShoot_Time > 0) 
            {
                gShoot_Time -= dt;
                gAnimation->Set_Props("Orc_Warrior_Attack_2", 1, 4, 250, gFlip);
                Repeat = true;
            } 
            else 
            { 
                if(gShoot_Time <= 0 and Crystal == nullptr) 
                {
                    Crystal = new Bullet(new Properties("Bullet_Move", gTransform->X, 288 + 73, 150, 120, gFlip));
                    Crystal->Set_Dam(gDamage);
//                    std::cout << gTransform->Y << '\n';
                    Crystal->Set_Dir(gDir);
//                    std::cout << gDir << '\n';
                }
                if(!gIs_Running)
                gAnimation->Set_Props(gTexture_ID, 1, 5, 150, gFlip);
                gShoot_Time = 5.0;
                Repeat = true;
            }
//            gAnimation->Set_Props("Orc_Warrior_Attack_2", 1, 4, 150, gFlip);

            Is_Insane();
        }
        else 
        { 
            gType = BOSS_INSANE;
            gIs_Shooting = false;
            Track_Tar();
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
            if(!gIs_Attacking and !gIs_Running)
            gAnimation->Set_Props(gTexture_ID, 1, 5, 150, gFlip);

            if(Is_Tar_Colly() != 0)
            {
                gIs_Attacking = true;
                gIs_Running = false;
            }
            else
            {
                gIs_Attacking = false;
                gIs_Running = true;
            }
            if(gIs_Attacking and gAttack_Time > 0)
            {
                gAttack_Time -= dt;
                Sound::Get_Instance()->PlayEffect("Orc_Attack");
            }
            else 
            {  
                gIs_Attacking = false;
                gAttack_Time = ATTACK_TIME;
            }
            if(gIs_Attacking)
            {
                gAnimation->Set_Props("Orc_Warrior_Attack_1", 1, 4, 150, gFlip);
            }
            if(gIs_Running)
            {
                gAnimation->Set_Props("Orc_Warrior_Run", 1, 6, 200, gFlip);
            }
        }
        if(gTarget->Is_Attacking()) 
        {
            gIs_Hurt = true;
        }
        if(gIs_Hurt and gHurt_Time > 0) 
        {
            Sound::Get_Instance()->PlayEffect("Orc_Die");
            gHurt_Time -= dt;
        }
        else 
        {
            gHurt_Time = 2.0;
            gIs_Hurt = false;
        }
        if(gIs_Hurt and !gIs_Insane) 
        {
            gAnimation->Set_Props("Orc_Warrior_Hurt", 1, 2, 100, gFlip);
            Repeat = true;
        }
        if(gHealth == 0)
        {
            gIs_Dead = true;
        }
        else 
        {
            gIs_Dead = false;
            Repeat = true;
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
    if(Crystal != nullptr) 
    {
        Crystal->Set_Tar_Box(gTarget->Get_Collider()->Get_Box());
        Crystal->Update(dt);
        if(Crystal->Get_Bullet_State())
        {
            delete Crystal;
            Crystal = nullptr;
        }
    }
    //
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

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;

    if(Crystal != nullptr) Crystal->Draw();

    Draw_Health();
}

void Boss::Draw_Health()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    Box.y -= 60;
    Box.h -= 67;
    Box.x -= 22;
    Box.w += 28;
    SDL_Rect H = Box;
//    std::cout << "H: " << Box.h << '\n';
//    std::cout << Box.w << "\n";
    H.w = double(gHealth*1.0 / gMax_Health) *80;
    Box.x--;
    Box.y--;
    Box.h++;
    Box.w+=2;
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
    if(Crystal != nullptr) Crystal->Clean();
 }