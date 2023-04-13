#pragma once

#include "../GameObject.hpp"
#include <string>

class Character: public GameObject
{
    public:
        Character(Properties* props): GameObject(props) {}
        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(double dt)=0;

    protected:
        std::string gName;
        
};