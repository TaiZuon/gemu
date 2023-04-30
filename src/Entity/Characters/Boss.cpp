#include "Boss.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"

Boss::Boss(Properties* props): Character(props)
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
    gCollider->Set_Empty(0,0,0,0);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY*2);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 5, 150, SDL_FLIP_NONE);
}

void Boss::Update(double dt)
{
    bool Reset = false;
    bool Repeat = true;

    gAnimation->Set_Props(gTexture_ID, 1, 5, 150, gFlip);

    gRigidBody->Update(dt, BOSS);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, BOSS_SIZE, BOSS_SIZE);
    gRigidBody->Update(dt, BOSS);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    gCollider->Set_Box(gTransform->X, gTransform->Y, BOSS_SIZE, BOSS_SIZE);

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

void Boss::Draw()
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
 //   Draw_Health();
}

void Boss::Draw_Health()
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
 void Boss::Clean()
 {
    TextureManager::Get_Instance()->Drop(gTexture_ID);
 }