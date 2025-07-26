#include "MapParser.h"
#include <sstream>
#include<iostream>

MapParser*  MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    return Parse("earth", "../assets/maps/map.tmx");
}

bool MapParser::Parse(std::string id, std::string source)
{
    tinyxml2::XMLDocument xml;
    xml.LoadFile(source.c_str());

    if (xml.Error())
    {
        std::cout<< "Failed to load: "<< source <<std::endl;
        return false;
    }
    
    tinyxml2::XMLElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;
    root->QueryIntAttribute("width", &colcount);
    root->QueryIntAttribute("height", &rowcount);
    root->QueryIntAttribute("tilewidth", &tilesize);

    TilesetList tilesets;
    for (tinyxml2::XMLElement* e=root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileSet(e));
        }
        m_Tilesets = tilesets; 
    }
    


    GameMap* gamemap = new GameMap();
    for (tinyxml2::XMLElement* e=root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayer.push_back(tilelayer);
        }
        
    }
    
    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileSet(tinyxml2::XMLElement* xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->QueryIntAttribute("firstgid", &tileset.FirstID);

    xmlTileset->QueryIntAttribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->QueryIntAttribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount/tileset.ColCount;
    xmlTileset->QueryIntAttribute("tilewidth", &tileset.Tilesize);

    tinyxml2::XMLElement* image = xmlTileset->FirstChildElement("image");
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
    tinyxml2::XMLElement* data;
    for(tinyxml2::XMLElement* e = xmlLayer->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
        {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
            {
                break;
            }
            
        }
        
    }
    
    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
    {
        it->second = nullptr;
    }
    m_MapDict.clear();
}