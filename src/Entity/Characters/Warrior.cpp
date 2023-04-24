#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"

Warrior::Warrior(Properties* props): Character(props)
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
    gAnimation->Set_Props(gTexture_ID, 1, 6, 100, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
    Draw_Health();
}

void Warrior::Draw_Health()
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
//    std::cout << "Hw: " << H.w << '\n';
    
//    std::cout << "Box: " << Box.x << " " << Box.y << '\n';
//    std::cout << "Cam: " << Cam.X << " " << Cam.Y << '\n';
//   std::cout << "transform: " << gTransform->X << " " << gTransform->Y << '\n';
//    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 255, 255, 0); 
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);
    SDL_SetRenderDrawColor(Game::Get_Instance()->gRenderer, 255, 50, 50, 0); 
    SDL_RenderFillRect(Game::Get_Instance()->gRenderer, &H); 
}

int Warrior::Get_Health()
{
    return gHealth;
}

void Warrior::Hurt(int dam)
{
    gHealth -= dam;
    gHealth = std::max(gHealth, 0);
//    std::cout << "Health: " << gHealth << '\n';
}

void Warrior::Update(double dt)
{
    bool Repeat = false;
    bool Reset = false;
//    std::cout << SDL_GetTicks() << "\n";
    if(!gIs_Dead)
    {
    if(gEnemy_Attack) 
    {
        gIs_Hurt = true;

    }
    if(gIs_Hurt and gHurt_Time > 0) 
    {
        gHurt_Time -= dt;
        Hurt(gEnemy_Dam);
    }
    else 
    {
        gHurt_Time = 2.0;
        gIs_Hurt = false;
    }
    if(gIs_Hurt) 
    {
        gAnimation->Set_Props("Warrior_Hurt", 1, 2, 100, gFlip);
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
    
    //neu V != 0 thi co ma sat (xet theo phuong X)
    if(std::abs(gRigidBody->Get_Velocity().X) != 0)
    {
        double v_temp = gRigidBody->Get_Velocity().X;
        Vector2D friction(-FRICTION * (v_temp/std::abs(v_temp)),0);
        gRigidBody->Apply_Friction(friction);
    } 
    else
    {
        gRigidBody->Unset_Friction();
    }

    //idle
    if(gIs_Landed and !gIs_Attacking and !gIs_Hurt and !gIs_Running) 
    {
        gAnimation->Set_Props(gTexture_ID, 1, 6, 200, gFlip);
        Repeat = true;
//        std::cout << "idle!\n";
    }
    gRigidBody->Unset_Force();
    gIs_Running = false;

    
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == 1 and !gIs_Attacking)
    {
        gRigidBody->Apply_ForceX(1 * 0.5);
        gIs_Running = true;
        gFlip = SDL_FLIP_NONE;
    }
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == - 1 and !gIs_Attacking)
    {
        gRigidBody->Apply_ForceX(-1 * 0.5);
        gIs_Running = true;
        gFlip = SDL_FLIP_HORIZONTAL;
    }

    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_I))
    {
        gRigidBody->Unset_Force();
        gIs_Attacking = true;
        Reset = true;
        Repeat = false;
    }
    if(gIs_Attacking and gAttack_Time > 0) 
    {
        gAttack_Time -= dt;
 //       std::cout << "gAttack_Time: " << gAttack_Time << '\n';
    }
    else 
    {
        gAttack_Time = ATTACK_TIME;
        gIs_Attacking = false;
    }

    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_J) and gIs_Landed)
    {
        gIs_Jumping = true; 
        Reset = true;
        gIs_Landed = false;
//        gRigidBody->Apply_ForceY( 1 * gJump_Force);
    }
    if(gIs_Jumping && gJump_Time > 0)
    {
        gAnimation->Set_Props("Warrior_Jump", 1, 3, 200, gFlip);
        Repeat = false;
        gJump_Time -= dt;
//        std::cout << gJump_Time << '\n';
        gRigidBody->Apply_ForceY( - gJump_Force);
    }
    else
    {
        gIs_Jumping = false;
        gJump_Time = JUMP_TIME;
    }

    if(gRigidBody->Get_Velocity().Y != 0 and !gIs_Landed) 
    {
        gIs_Falling = true;
    }
    else gIs_Falling = false;

//    std::cout << gIs_Jumping << '\n';
    // if(gIs_Jumping)
    // {
    //     gAnimation->Set_Props("Warrior_Jump", 1, 3, 200, gFlip);
    // } 
    if(gIs_Running)
    {
        gAnimation->Set_Props("Warrior_Run", 1, 6, 100, gFlip);
        Repeat = true;
    }
//        std::cout << gIs_Running << " " << gFlip << '\n';
    if(gIs_Attacking)
    {
        gAnimation->Set_Props("Warrior_Attack_1", 1, 4, 150, gFlip);
        Repeat = false;
    }

    if(gIs_Falling)
    {
        gAnimation->Set_Props("Warrior_Fall", 1, 2, 200, gFlip);
        Repeat = false;
    }
    }
    else
    {
        Dead();
        gAnimation->Set_Props("Warrior_Dead", 1, 4, 100, gFlip);
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gRigidBody->Stop_Vel_Y();
    }

    gRigidBody->Update(dt);

    gLast_Safe_Position.X = gTransform->X;
//    gTransform->TranslateX(gRigidBody->Get_Position().X);
//    std::cout << "Pos:" << gRigidBody->Get_Position().X << "\n";
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, 96, 96);
//    std::cout << "Trans: " << gTransform->X << "\n";
//    std::cout << "Box 1: " << gCollider->Get_Box().x << " " << gCollider->Get_Box().y << '\n';

    // if(CollisionHandler::Get_Instance()->Is_Map_Collision(gCollider->Get_Box()))
    // {
    //     gTransform->X = gLast_Safe_Position.X;
    // }

    gRigidBody->Update(dt);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    // std::cout << "Last Safe: " << gLast_Safe_Position.Y << '\n';
    // std::cout << "Transform: " << gTransform->Y << '\n';
    gCollider->Set_Box(gTransform->X, gTransform->Y, 96, 96);
//    std::cout << "Box 2: " << gCollider->Get_Box().x << " " << gCollider->Get_Box().y << '\n';
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

    gAnimation->Update(dt, Repeat, Reset);

}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}