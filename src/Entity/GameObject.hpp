#pragma once

#include "IObject.hpp"
#include "../Physics/Transform.hpp"
#include "../Physics/Point.hpp"

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
            
            double center_x = props->X + props->Width/2;
            double center_y = props->Y + props->Height/2;
            gOrigin = new Point(center_x, center_y);
        }

        Point* Get_Origin()
        {
            return gOrigin;
        }
        // SDL_Rect Get_Box()
        // {
        //     SDL_Rect a;
        //     a.x = gOrigin->X;
        //     a.y = gOrigin->Y;
        //     a.w = gWidth;
        //     a.h = gHeight;
        //     return a;
        // }
        virtual void Draw()=0;
        virtual void Update(double dt){}
        virtual void Clean()=0;

    protected:

        Point* gOrigin;

        Transform* gTransform;
        int gWidth, gHeight;
        SDL_RendererFlip gFlip;
        std::string gTexture_ID;
};