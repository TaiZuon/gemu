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
        // void Take_Dam(int dam)
        // {
        //     gHealth -= dam;
        // }
        // void Set_Health(int h)
        // {
        //     gHealth = h;
        // }
        // void Increase_Health(int dh)
        // {
        //     gHealth += dh;
        // }
        // void Set_Damage(int dam)
        // {
        //     gDamage = dam;
        // }

    protected:
        std::string gName;
        int gHealth;
        int gDamage;

        
};