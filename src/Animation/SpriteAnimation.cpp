#include "SpriteAnimation.h"
#include "Graphics/TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat){}

void SpriteAnimation::Draw(float x, float y, int width, int height, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::Update(float dt)
{
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}