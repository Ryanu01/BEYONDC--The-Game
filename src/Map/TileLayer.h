#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include<string>
#include<vector>

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, Tilesize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
private:
    int m_TileSize;
    int m_RowCount, m_ColCount;

    TileMap m_Tilemap;
    TilesetList m_Tilesets;
    std::string m_Name;
public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets, const std::string& name);
    virtual void Render();
    std::string GetName() const { return m_Name; }
    virtual void Update();
    inline int GetTileSize(){return m_TileSize;}
    inline int GetWidth(){return m_ColCount;}
    inline int GetHeight(){return m_RowCount;}
    inline TileMap GetTilemap(){return m_Tilemap;}
};

#endif