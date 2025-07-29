#include "TextureManager.h"
#include "Engine.h"
#include "Camera/Camera.h"
#include "Vendor/tinyxml2.h"

TextureManager* TextureManager::s_instance = nullptr;

bool TextureManager :: LoadTexture(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Error creating surface %s error: %s\n",filename.c_str(), SDL_GetError());
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Error creating texture : %s\n", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;

    return true;
    
}

void TextureManager :: Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};    
    Vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio;
    SDL_Rect destRect = {static_cast<int>(x -cam.X), static_cast<int>(y - cam.Y), static_cast<int>(width*scaleX), static_cast<int>(height*scaleY)};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager :: DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    SDL_Rect dstrect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstrect, 0, nullptr, flip);
}

void TextureManager:: DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect destRect = {static_cast<int>(x -cam.X), static_cast<int>(y - cam.Y), tileSize, tileSize};

    SDL_Rect srcRect = {tileSize*frame, tileSize*row, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager :: Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

bool TextureManager:: ParseTexture(std::string source)
{
    tinyxml2::XMLDocument xml;
    xml.LoadFile(source.c_str());
    if(xml.Error())
    {
        std::cout<<"Failed to load: "<<source<<std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = xml.RootElement();
    for(tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("texture")){
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            LoadTexture(id,"../assets/" + src);
        }
    }
    return true;
}

// TextureManager.cpp
SDL_Texture* TextureManager::GetTexture(std::string id)
{
    return m_TextureMap[id];
}


void TextureManager :: clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }

    m_TextureMap.clear();
    SDL_Log("Texture map cleaned!\n");
}

