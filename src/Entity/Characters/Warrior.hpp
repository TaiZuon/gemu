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

    int Get_Health();
    void Hurt(int dam);
    void Dead()
    {
        gIs_Jumping = false;
        gIs_Falling = false;
        gIs_Running = false;
        gIs_Attacking = false;
        gIs_Landed = false; 
        gIs_Hurt = false;
    }
    void Draw_Health();

    SDL_Rect gEnemy_Box;
    void Up_Enemy_Dam(int dtDam)
    {
        
        gEnemy_Dam += dtDam;
    } 
    void Set_Enemy_Box(SDL_Rect a)
    {
        gEnemy_Box = a;
    }

    bool gEnemy_Attack;
    int gEnemy_Dam;

    void Set_Enemy_State(bool a)
    {
        gEnemy_Attack = a;
    }
    void Set_Enemy_Dam(int a)
    {
        gEnemy_Dam = a;
    }
    int Get_Damage()
    {
        return gDamage;
    }
    bool Is_Attacking()
    {
        return gIs_Attacking;
    }
    RigidBody* Get_RigidBody()
    {
        return gRigidBody;
    }
    Collider* Get_Collider()
    {
        return gCollider;
    }
private:

    int gHealth = 2500;
    int gDamage = 5;

    bool gIs_Jumping;
    bool gIs_Falling;
    bool gIs_Running;
    bool gIs_Attacking;
    bool gIs_Landed;

    bool gIs_Hurt;
    bool gIs_Dead;

    double gAttack_Time;
    double gJump_Time;
    double gJump_Force;
    double gHurt_Time = 2.0;
    double gDead_Time = 2.0;

    Animation* gAnimation;
    RigidBody* gRigidBody;

    Collider* gCollider;
    
    Vector2D gLast_Safe_Position;

};