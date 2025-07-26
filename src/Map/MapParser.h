#ifndef MAPPARSER_H
#define MAPPARSER_H
#include <map>
#include<string>
#include "GameMap.h"
#include "TileLayer.h"
#include "Vendor\tinyxml2.h"

class MapParser
{
private:
    MapParser(){}
    static MapParser* s_Instance;
    std::map<std::string, GameMap*> m_MapDict;
    std::vector<Tileset> m_Tilesets;

private:
    bool Parse(std::string id, std::string source);
    Tileset ParseTileSet(tinyxml2::XMLElement* xmlTileset);
    TileLayer* ParseTileLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
public:
    bool Load();
    void Clean();

    inline GameMap* GetMaps(std::string id){return m_MapDict[id];}
    inline static MapParser* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();}
    
};

#endif