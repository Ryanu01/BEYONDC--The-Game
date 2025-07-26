#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>


class Input
{
private:
    Input();
    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;
    static Input* s_Instance;

public:
    static Input* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Input;
    }
    
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

};

#endif    