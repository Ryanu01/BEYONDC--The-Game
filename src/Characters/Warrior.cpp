#include "Warrior.h"
#include "Inputs/Input.h"
#include "Graphics\TextureManager.h"
#include<SDL2/SDL.h>
#include "Physics\Transform.h"
#include "Collision/CollisionHandler.h"
#include "Camera/Camera.h"
#include "Factory/ObjectFactory.h"

Warrior* Warrior::s_Instance = nullptr;
static Registrar<Warrior> registrar("PLAYER");


Warrior ::Warrior(Properties* props) : Character(props)
{
    s_Instance = this;
    m_IsRunning = false;
    m_IsAttacking = false;
    m_IsGrounded = false;
    m_IsJumping = false;
    
    m_Flip = SDL_FLIP_NONE;
    
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTIme = ATTACK_TIME;
    
    
    m_Collider = new Collider();
    m_Collider->SetBuffer(10, 5, 71, 65);
    
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);
    
    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 1, 8, 150);
}

Warrior* Warrior::GetInstance()
{
    return s_Instance;

}
void Warrior :: Draw()
{
    Vector2D cam = Camera::GetInstance()->GetPosition();
    m_Animation->Draw(m_Transform->X - cam.X, m_Transform->Y - cam.Y, m_Width, m_Height, m_Flip);
    // m_Collider->Draw();
}

Vector2D Warrior :: Getproperorigin() 
{
    float originX = m_Transform->X + (m_Width * 0.5f);
    float originY = m_Transform->Y + (m_Height * 0.5f);
    return Vector2D(originX, originY);
}

void Warrior::Update(float dt)
{
    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    //Attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }

    // JUMP
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    
    //Fall
    if(m_RigidBody->Velocity().Y > 0 && !m_IsGrounded)
    {
        m_IsFalling = true;
    }else
    {
        m_IsFalling = false;
    }
    
    //Attack timer
    if(m_IsAttacking && m_AttackTIme > 0)
    {
        m_AttackTIme -= dt;
    }else
    {
        m_IsAttacking = false;
        m_AttackTIme = ATTACK_TIME;
    }

    // Move along x axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    // Move along y axis
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


    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;
    AnimationState();
    
    m_Animation->Update(dt);
}


void Warrior::AnimationState()
{
    if (m_IsAttacking)
    {
        m_Animation->SetProps("player_attack", 1, 8, 90);
    }
    else if (m_IsJumping)
    {
        m_Animation->SetProps("player_jump", 1, 8, 100);
    }
    else if (m_IsFalling)
    {
        m_Animation->SetProps("player_falling", 1, 4, 100);
    }
    else if (m_IsRunning)
    {
        m_Animation->SetProps("player_run", 1, 8, 60);
    }
    else
    {
        m_Animation->SetProps("player", 1, 2, 200); // idle
    }
}


void Warrior ::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}