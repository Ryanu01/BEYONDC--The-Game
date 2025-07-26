#include "Warrior.h"
#include "Inputs/Input.h"
#include "Graphics\TextureManager.h"
#include<SDL2/SDL.h>
#include "Physics\Transform.h"
#include "Collision/CollisionHandler.h"
#include "Camera/Camera.h"
Warrior ::Warrior(Properties* props) : Character(props)
{
    m_JumpForce = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 8, 150, SDL_FLIP_NONE);
}

void Warrior :: Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}


void Warrior::Update(float dt)
{
    m_Animation->SetProps("player", 1, 2, 100, SDL_FLIP_NONE);
    m_RigidBody->UnSetForce();
    
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_RigidBody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps("player_run", 1, 8, 60, SDL_FLIP_HORIZONTAL);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {
        m_RigidBody->ApplyForceX(5*FORWARD);
        m_Animation->SetProps("player_run", 1, 8, 60, SDL_FLIP_NONE);
    }
    
    
    
    //JUMP
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    
    //move along x axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }
    
    //move along the y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }
    
    // m_Transform->TranslateX(m_RigidBody->Position().X);
    // m_Transform->TranslateY(m_RigidBody->Position().Y);
    
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
    
}
void Warrior ::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}