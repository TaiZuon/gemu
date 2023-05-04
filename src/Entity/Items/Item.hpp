#pragma once

#include "../GameObject.hpp"
#include "../../Animation/Animation.hpp"
#include "../../Physics/RigidBody.hpp"
#include "../../Physics/Collider.hpp"
#include "../../Physics/CollisionHandler.hpp"
#include "../../Constant.hpp"

class Item: public GameObject
{
public:
    Item(Properties *prop): GameObject(prop){}
    virtual void Draw()=0;
    virtual void Clean()=0;
    virtual void Update(double dt)=0;
protected:
    Animation* gAnimation;
    Collider* gCollider;
};

