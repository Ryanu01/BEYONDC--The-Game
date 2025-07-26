#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "Layer.h"
#include<vector>

class GameMap
{
private:
    friend class MapParser;
    std::vector<Layer*> m_MapLayer;

public:
    void Render()
    {
        for (unsigned int i = 0; i < m_MapLayer.size(); i++)
        {
            m_MapLayer[i]->Render();
        }
        
    }
    
    void Update()
    {
        for (unsigned int i = 0; i < m_MapLayer.size(); i++)
        {
            m_MapLayer[i]->Update();
        }
        
    }

    std::vector<Layer*> GetMapLayers(){return m_MapLayer;}

};

#endif