#include "Enemy.h"
#include "Camera/Camera.h"
#include "Collision/CollisionHandler.h"
#include "Warrior.h"
#include "Graphics/TextureManager.h"
#include<iostream>

float scale = 0.6f;

Enemy::Enemy(Properties* props) : Character(props) {
    std::cout << "[LOG] Enemy constructor start\n";
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);
    m_Collider = new Collider();

    // Just call ParseTexture normally
    TextureManager::GetInstance()->ParseTexture("../assets/textures.tml");

    // Setup animation
    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("../assets/animation.aml");

    // Check if sequence exists before setting it
    if (!m_Animation->HasSequence("soldier_idle")) {
        std::cerr << "[ERROR] Animation 'soldier_idle' not found in animation.aml!\n";
    } else {
        m_Animation->SetCurrentseq("soldier_idle");
    }
}



void Enemy :: Draw()
{   
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, scale, scale, SDL_FLIP_HORIZONTAL);    
    m_Collider->Draw();
}



void Enemy::Update(float dt)
{
Warrior* player = Warrior::GetInstance();
if (!player)
{
    std::cout << "[ERROR] Warrior instance is null!" << std::endl;
    return;
}

    Vector2D playerPos = Warrior::GetInstance()->Getproperorigin();
    Vector2D enemyPos = Vector2D(
        m_Transform->X + 146 * 0.5f,
        m_Transform->Y + 146 * 0.5f
    );

    float dx = playerPos.X - enemyPos.X;
    float dy = playerPos.Y - enemyPos.Y;
    float distance = sqrt(dx*dx + dy*dy);

    if(distance <= m_DetectionRadius)
    {
        Vector2D direction(dx, dy);
        direction.Normalize();
        m_RigidBody->SetVelocity(direction * m_Speed);
        m_Ischasing = true;
    }else
    {
        m_RigidBody->SetVelocity(Vector2D(0,0));
        m_Ischasing = false;
    }

    //X Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 146 * scale, 172 * scale); //Might need to change
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 72 * scale, 86 * scale); //Might need to change

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    //Y Axis Movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 146 * scale, 172* scale); //MIght need to change
    // m_Collider->Set(m_Transform->X, m_Transform->Y, 72 * scale, 86* scale); //MIght need to change

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    if(m_Ischasing && m_Animation->GetCurrentSeq() != "soldier_run")
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_run");
    }
    else if(!m_Ischasing && m_Animation->GetCurrentSeq() != "soldier_idle")
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_idle");
    }

    m_Animation->Update(dt);

    if(m_Animation->IsEnded())
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_idle");
    }
}

void Enemy :: Clean()
{
    std::cout << "Enemy cleaned up.\n";
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}
