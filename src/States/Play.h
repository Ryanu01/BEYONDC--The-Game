#ifndef PLAY_H
#define PLAY_H

#include<iostream>
#include "Map/GameMap.h"
#include "Object/GameObject.h"
#include "GameState.h"
#include "Characters/Enemy.h"
#include "Characters/Warrior.h"
#include "Timer/Timer.h"
#include "Menu.h"
#include "Inputs/Input.h"
#include "Camera/Camera.h"
#include "Map/MapParser.h"
#include "Map/TileLayer.h"
#include "Factory/ObjectFactory.h"
#include "Graphics/TextureManager.h"
#include "Collision/CollisionHandler.h"

class Play : public GameState
{
private:
    static void OpenMenu();
    static void PauseGame();

private:
    bool m_EditMode;
    GameMap* m_LevelMap;
    std::vector<GameObject*> m_GameObjects;

public:
    Play();
    void Events();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();
    
    // inline GameMap* GetMap(){return m_LevelMap;}
    
};



#endif