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
int Warrior::Is_Killed()
{
    if(gIs_Killed) return 1;
    else return 0;
}
int Warrior::Get_Dir()
{
    if(gFlip == SDL_FLIP_NONE) return FORWARD;
    if(gFlip == SDL_FLIP_HORIZONTAL) return BACKWARD;
}
int Warrior::Get_Damage()
{
    return gDamage;
}
bool Warrior::Is_Dead()
{
    return gIs_Dead;
}
bool Warrior::Is_Attacking()
{
    return gIs_Attacking;
}
void Warrior::Heal(int a)
{
    gHealth = std::min(gMax_Health, gHealth + a);

}

void Warrior::Hurt(double dt)
{
//    std::cout << "Hurt: " << gIs_Hurt << "\n";
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    {
        if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Attacking() and !ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Dead()) 
        {
            gIs_Hurt = true;
        }
        if(gHurt_Time > 0 and gIs_Hurt) 
        {
            gHurt_Time -= dt;
            gAnimation->Set_Props("Warrior_Hurt", 1, 2, 100, gFlip);
        }
        else 
        {
            gHurt_Time = 0.2;
            gIs_Hurt = false;
        }
    }
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++)
    {
        if(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Attacking() and !ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Dead()) 
        {
            gIs_Hurt = true;
        }
        if(gHurt_Time > 0 and gIs_Hurt) 
        {
            gHurt_Time -= dt;
            gAnimation->Set_Props("Warrior_Hurt", 1, 2, 100, gFlip);
        }
        else 
        {
            gHurt_Time = 0.2;
            gIs_Hurt = false;
        }
    }
}
void Warrior::Take_Dam(int dam)
{
    gHealth -= dam;
    gHealth = std::max(gHealth, 0);
    gHealth = std::min(gHealth, gMax_Health);
}
void Warrior::Jump(double dt)
{
//    std::cout << "Jump time: " << gJump_Time << "\n";
    if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_W) and gIs_Landed and !gIs_Attacking)
    {
//        std::cout << "Jump reset\n";
        gAnimation->AnimationStart();
        gIs_Jumping = true;
        gIs_Landed = false;
    }
    if(gIs_Jumping && gJump_Time > 0)
    {
        gJump_Time -= dt;
        gRigidBody->Apply_ForceY(- gJump_Force);
    }
    else
    {
        if(gJump_Time < 0) gRigidBody->Unset_Force();
        gIs_Jumping = false;
        gJump_Time = JUMP_TIME;
    }
    if(gIs_Jumping or !gIs_Landed)
    {
        gAnimation->Set_Props("Warrior_Jump", 1, 3, 100, gFlip);
    }
}
void Warrior::Attack()
{
    if(!gIs_Attacking) 
    {
        gAnimation->AnimationStart();
        // std::cout << "Atk reset\n";
    }
    gIs_Attacking = true;
    gRigidBody->Unset_Force();
    gAnimation->Set_Props("Warrior_Attack_1", 1, 4, 150, gFlip);    
    if(gAnimation->Get_Frame() >= 3 and gAnimation->Is_New_Frame()) 
    {
        Sound::Get_Instance()->PlayEffect("Attack");
        for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++ )
        {
            if(ObjectHandler::Get_Instance()->Get_Enemy(i)->Is_Taken_Dam())
            {
                ObjectHandler::Get_Instance()->Get_Enemy(i)->Hurt(gDamage);
            }
        }
        for( int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++ )
        {
            if(ObjectHandler::Get_Instance()->Get_Boss(i)->Is_Taken_Dam())
            {
                ObjectHandler::Get_Instance()->Get_Boss(i)->Hurt(gDamage);
            }
        }
    }
}
void Warrior::Dead()
{
    double dt = Timer::Get_Instance()->Get_Delta_Time();
    gDead_Time -= dt;

    gAnimation->Set_Props("Warrior_Dead", 1, 4, 200, gFlip);
    gRigidBody->Unset_Force();
    gRigidBody->Stop_Vel_X();
    if(gDead_Time <= 0)
    {
        Sound::Get_Instance()->PlayEffect("Dead");
        gIs_Killed = true;
    }
    else gIs_Killed = false;
    gIs_Jumping = false;
    gIs_Falling = false;
    gIs_Running = false;
    gIs_Attacking = false;

}
void Warrior::Idle()
{
    gIs_Attacking = false;
    gIs_Jumping = false;
    gIs_Running = false;
    gAnimation->Set_Props(gTexture_ID, 1, 6, 200, gFlip);
    gRigidBody->Unset_Force();
}
void Warrior::Run()
{
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == FORWARD and !gIs_Attacking)
    {
        gDirection = FORWARD;
        gIs_Running = true;
        gFlip = SDL_FLIP_NONE;
    }
    if(Input::Get_Instance()->Get_Direction(HORIZONTAL) == BACKWARD and !gIs_Attacking)
    {
        gDirection = BACKWARD;
        gIs_Running = true;
        gFlip = SDL_FLIP_HORIZONTAL;
    }
    if(gIs_Running)
    {
        Sound::Get_Instance()->PlayEffect("Running");
        gAnimation->Set_Props("Warrior_Run", 1, 6, 100, gFlip);
        gRigidBody->Apply_ForceX( gDirection * RUN_FORCES[WARRIOR] );
    }    
    else
    {
        gRigidBody->Unset_Force();
    }
}
void Warrior::Fall()
{
    if(gRigidBody->Get_Velocity().Y != 0 and !gIs_Landed) 
    {
        gIs_Falling = true;
        
    }
    if(std::abs(gRigidBody->Get_Velocity().Y) <= 0.01 and !gIs_Landed)
    {
        gAnimation->AnimationStart();
//        std::cout << "Fall reset\n";
    }
    else gIs_Falling = false;
    if(gIs_Falling)
    {
        gAnimation->Set_Props("Warrior_Fall", 1, 2, 75, gFlip);
    }
}
void Warrior::Friction()
{
//    std::cout << gRigidBody->Get_Friction().X << '\n';
//        std::cout << gRigidBody->Get_Velocity().X << "\n";
    if(std::abs(gRigidBody->Get_Velocity().X) >= 0.01)
    {
        double v_temp = gRigidBody->Get_Velocity().X;
        Vector2D friction(-FRICTION * (v_temp/std::abs(v_temp)),0);
        gRigidBody->Apply_Friction(friction);
    } 
}
void Warrior::Update(double dt)
{
    bool Repeat = false;
    bool Reset = false;
    if(!gIs_Dead and !gIs_Killed)
    {
        if(gHealth == 0)
        {
            gIs_Dead = true;
        }
        else 
        {
            gIs_Dead = false;
        }
        //friction
        Friction();
        //idle
        if(Input::Get_Instance()->No_Key_Down())
        {
            Idle();
        }
        gIs_Running = false;
        
        //hurt
        Hurt(dt);

        //run    
        Run();

        //jump
        Jump(dt);

        //fall
        Fall(); 

        //attack
        if(Input::Get_Instance()->Get_Key_Down(SDL_SCANCODE_I)) 
        {
            Attack();
        }
    }
    else if(gIs_Dead)
    {
        Dead();
    }

    gRigidBody->Update(dt, WARRIOR);

    gLast_Safe_Position.X = gTransform->X;
    gTransform->X+=gRigidBody->Get_Position().X;
    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);
    //check border of window
    if(gTransform->X <= -35 or gTransform->X > (1860))
    {
        gTransform->X = gLast_Safe_Position.X;
    }
    //check block to every enemy
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Enemies(); i++)
    {
        if(CollisionHandler::Get_Instance()->Is_Collision(Get_Collider()->Get_Box(), ObjectHandler::Get_Instance()->Get_Enemy(i)->Get_Collider()->Get_Box()) == gDirection)
        gTransform->X = gLast_Safe_Position.X;
    }
    //check block to every boss
    for(int i = 0; i < ObjectHandler::Get_Instance()->Get_Num_Bosses(); i++)
    {
        if(CollisionHandler::Get_Instance()->Is_Collision(Get_Collider()->Get_Box(), ObjectHandler::Get_Instance()->Get_Boss(i)->Get_Collider()->Get_Box()) == gDirection)
        gTransform->X = gLast_Safe_Position.X;
    }

    gRigidBody->Update(dt, WARRIOR);

    gLast_Safe_Position.Y = gTransform->Y;
    gTransform->Y+=gRigidBody->Get_Position().Y;
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

    gOrigin->X = gTransform->X + gWidth/2;
    gOrigin->Y = gTransform->Y + gHeight/2;

    gAnimation->Update(dt, Repeat, Reset);

}

void Warrior::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}