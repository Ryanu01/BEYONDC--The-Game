#include "Enemy.h"
#include "Camera/Camera.h"
#include "Collision/CollisionHandler.h"
#include "Warrior.h"
#include "Graphics/TextureManager.h"
#include <iostream>

Enemy::Enemy(Properties *props) : Character(props)
{
    std::cout << "[LOG] Enemy construct or start\n";
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);
    m_Collider = new Collider();

    // Just call ParseTexture normally
    TextureManager::GetInstance()->ParseTexture("../assets/textures.tml");

    // Setup animation
    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("../assets/animation.aml");

    // Check if sequence exists before setting it
    if (!m_Animation->HasSequence("soldier_idle"))
    {
        std::cerr << "[ERROR] Animation 'soldier_idle' not found in animation.aml!\n";
    }
    else
    {
        m_Animation->SetCurrentseq("soldier_idle");
    }
}

void Enemy::Update(float dt)
{
    Warrior* player = Warrior::GetInstance();
    if (!player)
    {
        std::cout << "[ERROR] Warrior instance is null!" << std::endl;
        return;
    }

    // Get player and enemy center positions
    Vector2D playerPos = player->Getproperorigin(); // Assumes center of player
    Vector2D enemyPos(
        m_Transform->X + 72 * 0.5f,  // Assuming enemy width is 72
        m_Transform->Y + 86 * 0.5f   // Assuming enemy height is 86
    );

    float dx = playerPos.X - enemyPos.X;
    float dy = playerPos.Y - enemyPos.Y;
    float distance = sqrt(dx * dx + dy * dy);

    // If player within detection radius, chase
    if (distance <= m_DetectionRadius)
    {
        Vector2D direction = Vector2D(dx, dy).Normalize();

        m_RigidBody->SetVelocity(direction * m_Speed);
        m_Ischasing = true;

        m_flip = (dx < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    }
    else
    {
        m_RigidBody->SetVelocity(Vector2D(0, 0));
        m_Ischasing = false;
    }

    m_RigidBody->Update(dt); // updates position delta

    // Save X and apply
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->PositionDelta().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 72 * 0.8f, 86 * 0.8f);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    // Save Y and apply
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->PositionDelta().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 72 * 0.8f, 86 * 0.8f);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    m_RigidBody->Reset(); // Clear position delta

    // Animation switching
    if (m_Ischasing && m_Animation->GetCurrentSeq() != "soldier_run")
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_run");
    }
    else if (!m_Ischasing && m_Animation->GetCurrentSeq() != "soldier_idle")
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_idle");
    }

    m_Animation->Update(dt);

    if (m_Animation->IsEnded())
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentseq("soldier_idle");
    }
}


void Enemy ::Draw()
{
    // Vector2D cam =  Camera::GetInstance()->GetPosition();
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 0.5f, 0.5f, m_flip);
    m_Collider->Draw();
}

void Enemy ::Clean()
{
    std::cout << "Enemy cleaned up.\n";
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}
