#ifndef WARRIOR_H
#define WARRIOR_H

#include "Physics\RigidBody.h"
#include "Animation\Animation.h"
#include "Character.h"

class Warrior : public Character
{
private:
    RigidBody* m_RigidBody;

    Animation* m_Animation;
    
public:
    Warrior(Properties *props);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();
    
};

#endif