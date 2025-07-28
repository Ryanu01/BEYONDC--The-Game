#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include<SDL2/SDL.h>
#include "Animation.h"

class SpriteAnimation : public Animation
{
private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
    std::string m_TextureID;
public:
    SpriteAnimation(bool repeat = true);
    virtual void Update(float dt);
    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

};

#endif
