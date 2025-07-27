#ifndef ANIMATION_H
#define ANIMATION_H 
#include<SDL2/SDL.h>
#include<iostream>

class Animation
{
private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    std::string m_TextureID;


public:
    Animation(){}

    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spriteRow, int FrameCount, int animSpeed);

};

#endif