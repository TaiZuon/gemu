#include "Warrior.hpp"
#include "../../TextureManager/TextureManager.hpp"
#include "SDL.h"
#include "../../Inputs/Input.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Game.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../ObjectHandler.hpp"
#include "Timer/Timer.hpp"

Warrior::Warrior(Properties* props): Character(props)
{
    Health::Get_Instance()->Get_Num_Health();
    gMax_Health = Health::Get_Instance()->Check_Num_Health();
    gHealth = gMax_Health;

    Damage::Get_Instance()->Get_Num_Damage();
    gMax_Damage = Damage::Get_Instance()->Check_Num_Damage(); 
    gDamage = gMax_Damage;

    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;
    gIs_Landed = false;
    gIs_Hurt = false;
    gIs_Dead = false;
    gIs_Killed = false;
    Un_Block();

    gJump_Time = JUMP_TIME;
    gJump_Force = JUMP_FORCE;

    gCollider = new Collider();
    gCollider->Set_Empty(-35,-50,70,50);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(GRAVITY);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 6, 100, SDL_FLIP_NONE);
    std::cout << "In New, player die? : " << gIs_Killed << "\n";
}
void Warrior::Reset_Position()
{
    gTransform->X = 100;
    gTransform->Y = 200;
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

int Warrior::Get_Health()
{
    return gHealth;
}

void Warrior::Heal(int a)
{
    gHealth = std::min(gMax_Health, gHealth + a);

}

void Warrior::Hurt(int dam)
{
    double dt = Timer::Get_Instance()->Get_Delta_Time();
    if(SDL_GetTicks() %1 ==0) gHealth -= dam;
    gHealth = std::max(gHealth, 0);
    gHealth = std::min(gHealth, gMax_Health);
    if(gHurt_Time > 0) 
    {
        gHurt_Time -= dt;
    }
    else 
    {
        gHurt_Time = 1.0;
        gIs_Hurt = false;
    }
    if(gIs_Hurt) 
    {
        gAnimation->Set_Props("Warrior_Hurt", 1, 2, 100, gFlip);
    }

}

void Warrior::Update(double dt)
{
    bool Repeat = false;
    bool Reset = false;

    if(!gIs_Dead and !gIs_Killed)
    {
    //    std::cout << gIs_Hurt << "\n";
    if(gEnemy_Attack and !gEnemy_Dead) 
    {
        gIs_Hurt = true;
    }
    else gIs_Hurt = false;
    // if(gIs_Hurt and gHurt_Time > 0) 
    // {
    //     gHurt_Time -= dt;
    // }
    // else 
    // {
    //     gHurt_Time = 1.0;
    //     gIs_Hurt = false;
    // }
    // if(gIs_Hurt) 
    // {
    //     gAnimation->Set_Props("Warrior_Hurt", 1, 2, 100, gFlip);
    //     Repeat = false;
    // }
    if(gHealth == 0)
    {
        gIs_Dead = true;
    }
    else 
    {
        gIs_Dead = false;
        Repeat = true;
    }
    //check neu enemy chet thi unblock
    if(gEnemy_Dead or gIs_Jumping) Un_Block();
    
    //neu V != 0 thi co ma sat (xet theo phuong X)
    if(std::abs(gRigidBody->Get_Velocity().X) >= 0.01)
    {
        double v_temp = gRigidBody->Get_Velocity().X;
        Vector2D friction(-FRICTION * (v_temp/std::abs(v_temp)),0);
        gRigidBody->Apply_Friction(friction);
    } 
    else
    {
        gRigidBody->Unset_Friction();
        gRigidBody->Stop_Vel_X();
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

    
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == FORWARD and !gIs_Attacking)
    {
//        gRigidBody->Apply_ForceX(1 * 0.5);
        gDirection = FORWARD;
        gIs_Running = true;
        gFlip = SDL_FLIP_NONE;
    }
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == BACKWARD and !gIs_Attacking)
    {
//        gRigidBody->Apply_ForceX(-1 * 0.5);
        gDirection = BACKWARD;
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
        Sound::Get_Instance()->PlayEffect("Attack");    
 //       std::cout << "gAttack_Time: " << gAttack_Time << '\n';
    }
    else 
    {
        gAttack_Time = ATTACK_TIME;
        gIs_Attacking = false;
    }
    //jump
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_W) and gIs_Landed)
    {
        gIs_Jumping = true; 
        Reset = true;
        gIs_Landed = false;
//        gRigidBody->Apply_ForceY( 1 * gJump_Force);
    }
    if(gIs_Jumping && gJump_Time > 0)
    {
        gAnimation->Set_Props("Warrior_Jump", 1, 3, 75, gFlip);
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
    //fall
    if(gRigidBody->Get_Velocity().Y != 0 and !gIs_Landed) 
    {
        gIs_Falling = true;
    }
    if(std::abs(gRigidBody->Get_Velocity().Y) <= 0.01 and !gIs_Landed)
    {
        Reset = true;
    }
    else gIs_Falling = false;

    if(gIs_Running and (gDirection != gIs_Blocked))
    {
        Sound::Get_Instance()->PlayEffect("Running");
        gAnimation->Set_Props("Warrior_Run", 1, 6, 100, gFlip);
        gRigidBody->Apply_ForceX( gDirection * RUN_FORCES[WARRIOR] );
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
        gAnimation->Set_Props("Warrior_Fall", 1, 2, 75, gFlip);
        Repeat = false;
    }
    }
    else if(gIs_Dead)
    {
        std::cout << "DT: " << gDead_Time << "\n";
        gDead_Time -= dt;

        gAnimation->Set_Props("Warrior_Dead", 1, 4, 200, gFlip);
        Repeat = false;
        Dead();
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
//        gRigidBody->Stop_Vel_Y();
        if(gDead_Time <= 0)
        {
            Sound::Get_Instance()->PlayEffect("Dead");
            gIs_Killed = true;
        }
        else gIs_Killed = false;
    }

    gRigidBody->Update(dt, WARRIOR);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);

    if(gTransform->X <= -35 or gTransform->X > (1860))
    {
        gTransform->X = gLast_Safe_Position.X;
    }
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    {
        if(CollisionHandler::Get_Instance()->Is_Collision(Get_Collider()->Get_Box(), ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Collider()->Get_Box()) != 0)
        gTransform->X = gLast_Safe_Position.X;
    }

    gRigidBody->Update(dt, WARRIOR);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
    // std::cout << "Last Safe: " << gLast_Safe_Position.Y << '\n';
    // std::cout << "Transform: " << gTransform->Y << '\n';
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);
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
    //neu !landed thi unblock
    if(gIs_Landed) Un_Block();


    gOrigin->X = gTransform->X + gWidth/2;
    gOrigin->Y = gTransform->Y + gHeight/2;

    gAnimation->Update(dt, Repeat, Reset);

}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}