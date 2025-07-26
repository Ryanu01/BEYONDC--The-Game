#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include<SDL2/SDL.h>
#include<vector>
#include "Map/TileLayer.h"
#include "Map/GameMap.h"


class CollisionHandler
{
private:
    CollisionHandler();
    TileMap m_CollisionTileMap;
    TileLayer* m_CollisionLayer;
    static CollisionHandler* s_Insatance;

public:
    bool MapCollision(SDL_Rect a);
    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    inline static CollisionHandler* GetInstance(){return s_Insatance = (s_Insatance != nullptr)? s_Insatance : new CollisionHandler();}
    
};

#endif