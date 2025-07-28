#ifndef ANIMATION_H
#define ANIMATION_H 
#include<SDL2/SDL.h>
#include<iostream>

class Animation
{
protected:
    bool m_Repeat;
    bool m_IsEnded;
    int m_CurrentFrame;


public:
    Animation(bool repeat = true) : m_Repeat(repeat){m_IsEnded = false;}

    virtual void Update(float dt) = 0;
    inline bool IsEnded(){return m_IsEnded;}
};

#endif