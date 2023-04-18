#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"

Warrior::Warrior(Properties* props): Character(props)
{
    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(0,0,0,0);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY*2);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 6, 40, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);

    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    SDL_Rect Box = gCollider->Get_Box();
    Box.x -= Cam.X;
    Box.y -= Cam.Y;
//    std::cout << "Box: " << Box.x << " " << Box.y << '\n';
//    std::cout << "Cam: " << Cam.X << " " << Cam.Y << '\n';
//   std::cout << "transform: " << gTransform->X << " " << gTransform->Y << '\n';
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &Box);

}

void Warrior::Update(double dt)
{
    
    //neu V != 0 thi co ma sat (xet theo phuong X)
    if(gRigidBody->Get_Velocity().X !=0)
    {
        double v_temp = gRigidBody->Get_Velocity().X;
        Vector2D friction(-FRICTION * (v_temp/std::abs(v_temp)),0);
        gRigidBody->Apply_Friction(friction);
    } 
    else gRigidBody->Unset_Friction();

    //idle
    gAnimation->Set_Props(gTexture_ID, 1, 6, 100, SDL_FLIP_NONE);
    gRigidBody->Unset_Force();

    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_A))
    {
        gAnimation->Set_Props("Warrior_Run", 1, 6, 100, SDL_FLIP_HORIZONTAL);
        gRigidBody->Apply_ForceX(-0.5);
    }
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_D))
    {
       gAnimation->Set_Props("Warrior_Run", 1, 6, 100, SDL_FLIP_NONE);
       gRigidBody->Apply_ForceX(0.5);
    }
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_U))
    {
       gAnimation->Set_Props("Warrior_Attack_1", 1, 4, 100, SDL_FLIP_NONE);
    }

    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_J) && gIs_Landed)
    {
        gIs_Jumping = true;
        gIs_Landed = false;
//        gRigidBody->Apply_ForceY( - gJump_Force);
    }
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_J) && gIs_Jumping && gJump_Time > 0)
    {
        gJump_Time -= dt;
//        std::cout << gJump_Time << '\n';
        gRigidBody->Apply_ForceY( - gJump_Force);
    }
    else 
    {
        gIs_Jumping = false;
        gJump_Time = JUMP_TIME;
    }


    gRigidBody->Update(dt);

    gLast_Safe_Position.X = gTransform->X;
//    gTransform->TranslateX(gRigidBody->Get_Position().X);
//    std::cout << "Pos:" << gRigidBody->Get_Position().X << "\n";
    gTransform->X+=gRigidBody->Get_Position().X;
//    gCollider->Set_Box(gTransform->X, gTransform->Y, 96, 96);
    std::cout << "Trans: " << gTransform->X << "\n";
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

    gAnimation->Update();
}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}