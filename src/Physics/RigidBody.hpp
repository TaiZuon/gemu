#pragma once

#include "Vector2D.hpp"

#define UNI_MASS 1.0f;
#define GRAVITY 9.8f;

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

    void Update(double dt)
    {
        gAccelaration.X = (gForce.X + gFriction.X) / gMass;
        gAccelaration.Y = gGravity + (gForce.Y + gFriction.Y) / gMass;
        gVelocity = gVelocity.ScalarMultiply_Vector(gAccelaration, dt);
        gPosition = gPosition.ScalarMultiply_Vector(gVelocity, dt);
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

};

