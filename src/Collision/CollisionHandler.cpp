#include "CollisionHandler.h"
#include "Engine.h"
#include<iostream>
CollisionHandler *CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer *)Engine::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTileMap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = 32;
    int RowCount = 20;
    int ColCount = 60;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w - 1) / tileSize;

    int top_tile = a.y/tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;


    if (left_tile < 0)
    {
        left_tile = 0;
    }
    if (right_tile > ColCount)
    {
        right_tile = ColCount;
    }

    if (top_tile < 0)
    {
        top_tile = 0;
    }
    if (bottom_tile > RowCount)
    {
        bottom_tile = RowCount;
    }

    for (int i = left_tile; i <= right_tile; ++i)
    {
        for (int j = top_tile; j <= bottom_tile; ++j)
        {
            if (m_CollisionTileMap[j][i] > 0)
            {
                return true;
            }

        }

    }


    return false;
}