#include "Menu.h"
#include "Play.h"
#include "Characters/Enemy.h"
#include "Inputs/Input.h"

Menu::Menu(){}

bool Menu::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    std::cout<< "Menu initialized" <<std::endl;
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);

    SDL_RenderPresent(m_Ctxt);
}

void Menu :: Update(){}

bool Menu :: Exit()
{
    std::cout<<"exit menu" << std::endl;
    return true;
}

//CallBacks
void Menu::StartGame()
{
    std::cout<<"Start Game\n";
}

void Menu :: Editor()
{
    std::cout<<"editor mode\n";
}

void Menu::Settings()
{
    std::cout<<"settings mode\n";
}

void Menu::Quit()
{
    std::cout<<"quit game\n";
}
