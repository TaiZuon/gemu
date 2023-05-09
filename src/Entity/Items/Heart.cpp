#include "Heart.hpp"
#include "../../Camera/Camera.hpp"
#include "../../SoundManager/Sound.hpp"

Heart::Heart(Properties * prop): Item(prop)
{
    gIs_Touched = false;

    gCollider = new Collider();
    gCollider->Set_Empty(-20,-20,40,40);

    gAnimation = new Animation();
    gAnimation->Set_Props(gTexture_ID, 1, 4, 150, SDL_FLIP_NONE);
}

void Heart::Set_Tar_Box(SDL_Rect a)
{
    gTar_Box = a;
}
int Heart::Is_Tar_Colly()
{
    return CollisionHandler::Get_Instance()->Is_Collision(gCollider->Get_Box(), gTar_Box);
}
int Heart::Get_Num_Heal()
{
    return gHeal;
}

void Heart::Update(double dt)
{
//    std::cout << Is_Tar_Colly() << '\n';
    bool Reset = true;
    bool Repeat = true;
    if(!gIs_Touched)
    {
        gAnimation->Set_Props(gTexture_ID, 1, 4, 150, SDL_FLIP_NONE);
        if(Is_Tar_Colly() != 0)
        {
            gIs_Touched = true;
            Sound::Get_Instance()->PlayEffect("Upgrade");
//            std::cout << "Heart touched!\n";
        }
    }

    gCollider->Set_Box(gTransform->X, gTransform->Y, HEART_SIZE, HEART_SIZE);
    SDL_Rect Box = gCollider->Get_Box();
//    std::cout << Box.x << " " << Box.y << " " << Box.w << " " << Box.h << '\n';
    gAnimation->Update(dt, Repeat, Reset);
}

void Heart::Draw()
{
    SDL_Rect a = gCollider->Get_Box();
    Vector2D Cam = Camera::Get_Instance()->Get_Position();
    a.x -= Cam.X;
    a.y -= Cam.Y;
    SDL_RenderDrawRect(Game::Get_Instance()->gRenderer, &a);

    gAnimation->Draw(gTransform->X, gTransform->Y, gWidth, gHeight);
}

void Heart::Clean()
{
    TextureManager::Get_Instance()->Drop(gTexture_ID);
}