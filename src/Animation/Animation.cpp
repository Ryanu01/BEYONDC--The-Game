#include "Animation.h"
#include "Graphics\TextureManager.h"


void Animation :: Update()
{
    m_SpriteFrame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Animation :: Draw(float x, float y, int sprietWidth, int spriteHeight, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, sprietWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}

void Animation :: SetProps(std::string textureID, int spriteRow, int FrameCount, int animSpeed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = FrameCount;
    m_AnimSpeed = animSpeed;

}