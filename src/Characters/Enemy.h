#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include "Physics/RigidBody.h"
#include "Physics/Collider.h"
#include "Animation/SeqAnimation.h"
#include "Animation/SpriteAnimation.h"

class Enemy : public Character
{
private:
    Collider* m_Collider;
    RigidBody* m_RigidBody;
    SeqAnimation* m_Animaton;
    Vector2D m_LastSafePosition;

public:
    Enemy(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
};

#endif