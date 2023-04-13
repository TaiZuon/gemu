#pragma once

#include "IObject.hpp"
#include "../Physics/Transform.hpp"

struct Properties
{
    int Width, Height;
    std::string Texture_ID;
    double X, Y;
    SDL_RendererFlip Flip;
    Properties(std::string textureID, double x, double y, int width, int height, SDL_RendererFlip flip)
    {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        Texture_ID = textureID;
    }    
};


class GameObject: public IObject
{
    public:
        GameObject(Properties* props) 
        { 
            gTexture_ID = props->Texture_ID;
            gWidth = props->Width;
            gHeight = props->Height;
            gFlip = props->Flip;
            gTransform = new Transform(props->X, props->Y);
        }
        virtual void Draw()=0;
        virtual void Update(double dt)=0;
        virtual void Clean()=0;

    protected:
        Transform* gTransform;
        int gWidth, gHeight;
        SDL_RendererFlip gFlip;
        std::string gTexture_ID;
};