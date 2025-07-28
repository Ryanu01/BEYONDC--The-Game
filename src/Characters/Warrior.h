#ifndef WARRIOR_H
#define WARRIOR_H

#include "Physics\RigidBody.h"
#include "Animation\SpriteAnimation.h"
#include "Character.h"
#include "Physics/Collider.h"
#include "Physics/Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 15.0f
#define RUN_FORCE 4.0F
#define ATTACK_TIME 20.0F 

class Warrior : public Character
{
private:
    RigidBody* m_RigidBody;
    SpriteAnimation* m_Animation;

    float m_JumpTime;
    float m_JumpForce;
    float m_AttackTIme;

    bool m_IsRunning;
    bool m_IsJumping;
    bool m_IsFalling;
    bool m_IsAttacking;
    bool m_IsGrounded;
    Collider* m_Collider;
    Vector2D m_LastSafePosition;
    
public:
    Warrior(Properties *props);

    virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();
    

private:
    void AnimationState();
};

#endif