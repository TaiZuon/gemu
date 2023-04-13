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
    void Set_Gravity(double Gravity)
    {
        gGravity = Gravity;
    }
    
};

