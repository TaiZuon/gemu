#include "About.hpp"
#include <fstream>
#include "TextureManager/TextureManager.hpp"
#include "Game.hpp"

About::About()
{
    gGS_Renderer = Game::Get_Instance()->gRenderer;
    gIs_Back = false;
    Load_About();
}
void About::Back()
{
    Game::Get_Instance()->PopState();
}
void About::Load_About()
{
    std::ifstream file ("data/About.txt");
    std::string s;
    while(!file.eof())
    {
        getline(file, s);
        std::string id = "line " + std::to_string(Num_lines);
        TextureManager::Get_Instance()->LoadText(id, s);
        std::cout << id << " loaded!\n";
        Num_lines++;
    }
    file.close();
}
void About::Draw_About()
{
    for(int i = 0; i < Num_lines; i++)
    {
        std::string id = "line " + std::to_string(i);
        TextureManager::Get_Instance()->DrawText(id, 40, 60 + i*35, 0, nullptr, SDL_FLIP_NONE);
    }
}

bool About::Init()
{
    mBack = new Button(new Properties("Back",SCREEN_WIDTH - 100, 5, 80, 80, SDL_FLIP_NONE));
    return true;
}

void About::Render()
{
    SDL_RenderClear(gGS_Renderer);
    SDL_SetRenderDrawColor(gGS_Renderer, 0, 200, 100, 255);

    TextureManager::Get_Instance()->Draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, nullptr, SDL_FLIP_NONE);

    mBack->Draw();
    Draw_About();

    SDL_RenderPresent(gGS_Renderer);
}

void About::Events()
{
    if(mBack->Get_Button_State() == MOUSE_DOWN)
    {
        gIs_Back = true;
        mBack->Set_Button_State(MOUSE_OUT);
    }
}
void About::Update()
{
    Events();
    if(!gIs_Back)
    {
        mBack->State_Update();
    }
    else 
    {
        gIs_Back = false;
        SDL_Delay(200);
        Back();
    }
}

void About::Clean()
{

}