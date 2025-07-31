#include "Play.h"

Play::Play(){
}

bool Play :: Init()
{
    m_EditMode = false;
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->ParseTexture("../assets/textures.tml");
    MapParser::GetInstance()->Load();
    m_LevelMap = MapParser::GetInstance()->GetMaps("earth");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetMapLayers().back();

    int tilesize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetWidth()*tilesize;
    int height = collisionLayer->GetHeight()*tilesize;

    Camera::GetInstance()->SetSceneLimit(width, height);
    CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTilemap(), tilesize);

    Warrior* player = new Warrior(new Properties("player_idle", 100, 200, 32, 32));
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    //GUI::GetInstance()->Init();
    std::cout<< "Play initialized" <<std::endl;

    return true;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
    SDL_RenderClear(m_Ctxt);

    m_LevelMap->Render();

    for(auto gameobj : m_GameObjects)
    {
        gameobj->Draw();
    }

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();
    
    /*if(m_EditMode){
        GUI::GetInstance()->draw(m_Ctxt);   
    }*/

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::Update()
{
    Events();

    if(!m_EditMode){
        float dt = Timer::GetInstance()->GetDeltaTime();

        for(auto gameobj : m_GameObjects){
            gameobj->Update(dt);
        }

        Camera::GetInstance()->Update(dt);
        m_LevelMap->Update();

    }
}

void Play::Events()
{
    // if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M))
    // {
    //     Engine::GetInstance()->ChangeState(new Menu());
    // }

    if(!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        m_EditMode = true;
        SDL_Delay(200);
    }

    if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5))
    {
        m_EditMode = false;
        SDL_Delay(200);
    }
}


bool Play :: Exit()
{
    m_LevelMap->Clean();
    delete m_LevelMap;
    for(auto gameobj : m_GameObjects)
    {
        gameobj->Clean();
        delete gameobj;
    }
    m_GameObjects.clear();
    TextureManager::GetInstance()->clean();
    std::cout<<"exit play"<<std::endl;
    return true;
}

// void Play::OpenMenu()
// {
//     Engine::GetInstance()->ChangeState(new Menu());
// }

void Play :: PauseGame()
{

}