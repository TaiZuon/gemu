#include "Bullet.hpp"
#include "../../Camera/Camera.hpp"
#include "../../SoundManager/Sound.hpp"
#include "Entity/ObjectHandler.hpp"

Bullet::Bullet(Properties* prop) : Item(prop)
{
    if(gTarget == nullptr) gTarget = ObjectHandler::Get_Instance()->Get_Player();
    gTime_Start = SDL_GetTicks();

    gIs_Touched = false;
    gIs_Done = false;

    gCollider = new Collider();
    gCollider->Set_Empty(-60,-90,60,90);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 2, 250, SDL_FLIP_NONE);

    gRigidBody = new RigidBody();
    gRigidBody->Set_Gravity(0);
    
}
int Bullet::Is_Tar_Colly()
{
    return CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTarget->Get_Collider()->Get_Box());
}
void Bullet::Explose(double dt)
{
        if(gEx_Time > 0)
        {
            gEx_Time -= dt;
            if(gEx_Time <= dt)
            {
                gIs_Done = true;
            }
        }
        gRigidBody->Unset_Force();
        gRigidBody->Stop_Vel_X();
        gAnimation->Set_Props("Bullet_Explose", 1, 3, 200, SDL_FLIP_NONE);
        Sound::Get_Instance()->PlayEffect("Crystal");
}


void Bullet::Update(double dt)
{
    bool Reset = true;
    bool Repeat = true;
    int gTime_Current = SDL_GetTicks();
    gRigidBody->Stop_Vel_Y();
    if(gTime_Current - gTime_Start >= BULLET_TIMELIFE) gIs_Touched = true;
    if(!gIs_Touched and !gIs_Done)
    {
        gAnimation->Set_Props(gTexture_ID, 1, 2, 250, SDL_FLIP_NONE);
        gRigidBody->Apply_ForceX(gDir * RUN_FORCES[BULLET]);
        if(Is_Tar_Colly()) 
        {
            gIs_Touched = true;
            if(gAnimation->Get_Frame() >= 2)
            gTarget->Take_Dam(gDam);
        }
    }
    else if(gIs_Touched)
    {
        Explose(dt);
    }
    gTransform->X+=gRigidBody->Get_Position().X;
    gTransform->Y+=gRigidBody->Get_Position().Y;

    gCollider->Set_Box(gTransform->X, gTransform->Y, CHAR_SIZE, CHAR_SIZE);
        
    gRigidBody->Update(dt, BULLET);
        
    gOrigin->X = gTransform->X + gWidth/2;   
    gOrigin->Y = gTransform->Y + gHeight/2;

    gAnimation->Update(dt, Repeat, Reset);
}

void Bullet::Draw()
{
    SDL_Rect a = gCollider->Get_Box();
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    a.x -= Cam.X;
    a.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &a);

    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
}

void Bullet::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}

