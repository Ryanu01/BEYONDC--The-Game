#include "Enemy.h"
#include "Camera/Camera.h"
#include "Collision/CollisionHandler.h"
#include "Graphics/TextureManager.h"
#include<iostream>

float scale = 0.6f;

Enemy::Enemy(Properties* props) : Character(props){
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);
    m_Collider = new Collider();

    m_Animaton = new SeqAnimation(false);
    m_Animaton->Parse("../assets/animation.aml");
    m_Animaton->SetCurrentseq("soldier_idle");
}

void Enemy :: Draw()
{
    m_Animaton->DrawFrame(m_Transform->X, m_Transform->Y, 0.6f, 0.6f, SDL_FLIP_HORIZONTAL);
    m_Collider->Draw();
}

void Enemy::Update(float dt)
{
    //X Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 146 * scale, 172 * scale); //Might need to change

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    //Y Axis Movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 146 * scale, 172* scale); //MIght need to change

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    m_Animaton->Update(dt);

    if(m_Animaton->IsEnded())
    {
        m_Animaton->SetRepeat(true);
        m_Animaton->SetCurrentseq("soldier_idle");
    }
}

void Enemy :: Clean()
{
    // std::cout << "Enemy cleaned up.\n";
    // delete m_Collider;
    // delete m_RigidBody;
    // delete m_Animaton;
}