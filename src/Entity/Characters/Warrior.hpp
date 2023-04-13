#include "Character.hpp"
#include "../../Animation/Animation.hpp"

class Warrior : public Character{
public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(double dt);

private:
    // int gRow, gFrame, gFrame_Count;
    // int gAnimation_Speed;
    Animation* gAnimation;
    
};