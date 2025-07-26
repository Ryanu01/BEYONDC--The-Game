#ifndef ENGINE_H
#define ENGINE_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Map/GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640


class Engine
{
private:
    static Engine* s_Instance;
    bool m_isRuning;
    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    Engine(){};


public:
   static Engine* GetInstance()
   {
    return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
   }
   bool init();
   bool clean();
   void Quit();

   void Update();
   void Render();
   void Events();


   inline GameMap* GetMap(){return m_LevelMap;}
   inline bool isRuning()
   {
    return m_isRuning;
   }

   inline SDL_Renderer* GetRenderer()
   {
    return m_Renderer;
   } 

};

#endif