#ifndef WARRIOR_H
#define WARRIOR_H

#include "Physics\RigidBody.h"
#include "Animation\Animation.h"
#include "Character.h"
#include "Physics/Collider.h"
#include "Physics/Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

class Warrior : public Character
{
private:
    RigidBody* m_RigidBody;
    Animation* m_Animation;

    bool m_IsJumping;
    bool m_IsGrounded;
    Collider* m_Collider;
    Vector2D m_LastSafePosition;
    
public:
    Warrior(Properties *props);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();
    
};

#endif