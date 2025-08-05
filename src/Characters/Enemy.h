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
    SeqAnimation* m_Animation;
    Vector2D m_LastSafePosition;
    float m_DetectionRadius = 200.0f;
    float m_Speed = 40.0f;
    bool m_Ischasing = false;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

public:
    Enemy(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
};

#endif