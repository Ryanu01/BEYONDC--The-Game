#ifndef COLLIDER_H
#define COLLIDER_H
#include<SDL2/SDL.h>
#include "Camera/Camera.h"
#include"Collision/CollisionHandler.h"
class Collider
{
private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;

public:
    inline SDL_Rect Get(){return m_Box;}
    inline void SetBuffer(int x, int y, int w, int h){m_Buffer = {x, y, w, h};}
    
    void Set(int x, int y, int w, int h)
    {
        m_Box = {
            x + m_Buffer.x,
            y + m_Buffer.y,
            w - (m_Buffer.x + m_Buffer.w),
            h - (m_Buffer.y + m_Buffer.h)
        };
    }

    void Draw()
    {
        Vector2D cam = Camera::GetInstance()->GetPosition();
        SDL_Rect box = {(int) (m_Box.x - cam.X), (int)(m_Box.y - cam.Y), m_Box.w, m_Box.h};
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    }
};

#endif