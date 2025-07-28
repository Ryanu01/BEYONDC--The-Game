#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<map>


class TextureManager
{
private:
    TextureManager(){};
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_instance;


public:
    
    static TextureManager* GetInstance()
    {
        return s_instance = (s_instance != nullptr)? s_instance : new TextureManager();
    }

    bool LoadTexture(std::string id, std::string filename);
    bool ParseTexture(std::string source);
    void Drop(std::string id);
    void clean();

    void Draw(std::string id, int x, int y, int width, int height,float scaleX = 1, float scaleY= 1, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
   
};

#endif