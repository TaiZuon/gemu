#include "Character.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Constant.hpp"

class Warrior : public Character{
public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);
    RigidBody* Get_RigidBody()
    {
        return gRigidBody;
    }
private:
    bool gIs_Jumping;
    bool gIs_Landed;

    double gJump_Time;
    double gJump_Force;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};