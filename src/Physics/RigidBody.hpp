#pragma once

#include "bits/stdc++.h"
#include "Vector2D.hpp"
#include "../Constant.hpp"

class RigidBody
{
private:
    double gMass;
    double gGravity;

    Vector2D gForce;   
    Vector2D gFriction;

    Vector2D gPosition;
    Vector2D gVelocity;
    Vector2D gAccelaration;

public:
    RigidBody()
    {
        gMass = UNI_MASS;
        gGravity = GRAVITY;
    }
    void Set_Mass(double Mass)
    {
        gMass = Mass;
    }
    double Get_Mass()
    {
        return gMass;
    }
    void Set_Gravity(double Gravity)
    {
        gGravity = Gravity;
    }

    void Apply_Force(Vector2D F)
    {
        gForce = F;
    }
    void Apply_ForceX(double Fx)
    {
        gForce.X = Fx;
    }
    void Apply_ForceY(double Fy)
    {
        gForce.Y = Fy;
    }
    void Unset_Force()
    {
        gForce = Vector2D(0,0);
    }

    void Apply_Friction(Vector2D Friction)
    {
        gFriction = Friction;
    }
    void Unset_Friction()
    {
        gFriction = Vector2D(0,0);
    }

    void Stop_Vel_X()
    {
        Unset_Force();
        gVelocity.X = 0;
        gPosition.X = 0;
     }
    void Stop_Vel_Y()
    {
        gVelocity.Y = 0;
        gPosition.Y = 0;
    }
    void Set_Vel_Y(double a)
    {
        gVelocity.Y = a;
    }

    void Update(double dt, int type)
    {
        gAccelaration.X = (gForce.X + gFriction.X) / gMass;
        gAccelaration.Y = gGravity + (gForce.Y + gFriction.Y) / gMass;
        
        gVelocity = gVelocity.Add_Vector(gVelocity, gVelocity.ScalarMultiply_Vector(gAccelaration, dt));

        if(gVelocity.X > MAX_VELOCITIES[type] or gVelocity.X < - MAX_VELOCITIES[type])
        {
            gVelocity.X = MAX_VELOCITIES[type] * (gVelocity.X / std::abs(gVelocity.X));
        } 
        gPosition = gPosition.ScalarMultiply_Vector(gVelocity, dt);
        if(std::abs(gPosition.X) <= 0.01) gPosition.X = 0;
        if(std::abs(gVelocity.X) <= 0.01) gVelocity.X = 0;
        if(std::abs(gPosition.Y) <= 0.01) gPosition.Y = 0;
        if(std::abs(gVelocity.Y) <= 0.01) gVelocity.Y = 0;
    }

    Vector2D Get_Position()
    {
        return gPosition;
    }
    Vector2D Get_Velocity()
    {
        return gVelocity;
    }
    Vector2D Get_Accelaration()
    {
        return gAccelaration;
    }
    Vector2D Get_Force()
    {
        return gForce;
    }
    Vector2D Get_Friction()
    {
        return gFriction;
    }

};

