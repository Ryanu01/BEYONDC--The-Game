#include "Engine.h"
#include <iostream>
#include "Graphics/TextureManager.h"
#include "Characters/Warrior.h"
#include "Inputs/Input.h"
#include "Timer/Timer.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"


Engine *Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine ::init()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL : %s\n", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        SDL_Log("Failed to initialize SDL_image: %s\n", IMG_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

    if (m_Window == nullptr)
    {
        SDL_Log("Error creating window : %s\n", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr)
    {
        SDL_Log("Error creating renderer : %s\n", SDL_GetError());
        return false;
    }

    if (!(MapParser::GetInstance()->Load()))
    {
        SDL_Log("Failed to Load map: %s", SDL_GetError());
    }
    
    m_LevelMap = MapParser::GetInstance()->GetMaps("earth");

    TextureManager::GetInstance()->LoadTexture("player", "../assets/warrior main.png");
    TextureManager::GetInstance()->LoadTexture("player_run", "../assets/run.png");

    player = new Warrior(new Properties("player", 100, 200, 32, 32));
    Transform tf;
    tf.Log();


    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_isRuning = true;
}

bool Engine ::clean()
{
    TextureManager::GetInstance()->clean();
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;
    IMG_Quit();
    SDL_Quit();

    m_isRuning = false;
    return true;
}

void Engine ::Quit()
{
    m_isRuning = false;
}

void Engine ::Update()
{   
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine ::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 210, 255, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap->Render();

    player->Draw();
    SDL_RenderPresent(m_Renderer);

}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}