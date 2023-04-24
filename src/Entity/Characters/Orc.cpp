#include "Orc.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"

Orc::Orc(Properties* props): Character(props)
{
    bool gIs_Jumping = false;
    bool gIs_Falling = false;
    bool gIs_Running = false;
    bool gIs_Attacking = false;
    bool gIs_Landed = false;
    bool gIs_Hurt = false;
    bool gIs_Dead = false;

    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(-35,-50,70,50);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY*2);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 5, 50, SDL_FLIP_NONE);
}

void Orc::Update(double dt)
{
    bool Reset = false;
    bool Repeat = false;
    if(!gIs_Dead)
    {
    if(gTar_Attack) 
    {
        gIs_Hurt = true;
    }
    if(gIs_Hurt and gHurt_Time > 0) 
    {
        gHurt_Time -= dt;
        Hurt(gTar_Dam);
    }
    else 
    {
        gHurt_Time = 2.0;
        gIs_Hurt = false;
    }
    if(gIs_Hurt) 
    {
        gAnimation->Set_Props("Orc_Hurt", 1, 2, 100, gFlip);
        Repeat = false;

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
    if(gIs_Dead and gDead_Time > 0)
    {
        gDead_Time -= dt;
    }
    if(gIs_Dead)
    {
        gAnimation->Set_Props("Warrior_Dead", 1, 4, 100, gFlip);
        Repeat = false;
        Dead();
    }

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

    if(Is_Tar_Colly())
    {
//        std::cout << "Touch!\n";
        gIs_Attacking = true;
        gIs_Running = false;
    }
    if(gIs_Attacking and gAttack_Time > 0)
    {
        gAttack_Time -= dt;
    }
    else 
    {
        gIs_Attacking = false;
        gAttack_Time = ATTACK_TIME;
    }
    if(std::abs(gOrigin->X - gTar->X) > 50 )
    {
//        std::cout << "Chase!\n";
        gIs_Running = true;
    }
    if(std::abs(gOrigin->X - gTar->X) > 5 and !gIs_Attacking)
    {
        if(gTar->X > gOrigin->X) 
        {
            gFlip = SDL_FLIP_NONE;
            gRigidBody->Apply_ForceX(0.5);
        }
        else 
        {
            gFlip = SDL_FLIP_HORIZONTAL;
            gRigidBody->Apply_ForceX(-0.5);
        }
    }
    else 
    {
//        std::cout << "Stop!\n";
        gRigidBody->Unset_Force();
        gIs_Running = false;
    }

    if(gIs_Attacking)
    {
        gAnimation->Set_Props("Orc_Attack_1", 1, 4, 150, gFlip);
    }
    if(gIs_Running)
    {
        gAnimation->Set_Props("Orc_Run", 1, 6, 100, gFlip);
    }
    }
    else
    {
        Dead();
        gAnimation->Set_Props("Orc_Dead", 1, 4, 100, gFlip);
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gRigidBody->Stop_Vel_Y();
    }


    gRigidBody->Update(dt);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, 96, 96);
    gRigidBody->Update(dt);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    gCollider->Set_Box(gTransform->X, gTransform->Y, 96, 96);

    SDL_Rect Box = gCollider->Get_Box();
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);

    if(CollisionHandler::Get_Instance()->Is_Map_Collision(gCollider->Get_Box()))
    {
//        std::cout << "Landed!\n";
        gIs_Landed = true;
        gTransform->Y = gLast_Safe_Position.Y;
//        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_Y();
    }
    else
    {
//      std::cout << "Not Landed!\n";
        gIs_Landed = false;
    }

    gOrigin->X = gTransform->X + gWidth/2;
    gOrigin->Y = gTransform->Y + gHeight/2;


//    std::cout << "Orc: " << gOrigin->X << " " << gOrigin->Y << '\n';
//    std::cout << "Tar: " << gTar->X << " " << gTar->Y << "\n";
    gAnimation->Update(dt, Repeat, Reset);
}

void Orc::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
//    std::cout << "Box: " << Box.x << " " << Box.y << '\n';
//    std::cout << "Cam: " << Cam.X << " " << Cam.Y << '\n';
//   std::cout << "transform: " << gTransform->X << " " << gTransform->Y << '\n';
//    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    Draw_Health();
}

void Orc::Draw_Health()
{
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    Box.y -= 15;
    Box.h -= 50;
    SDL_Rect H = Box;
    H.w = std::max(gHealth/100, 0);
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