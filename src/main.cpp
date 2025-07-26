#include "Engine.h"
#include "Timer/Timer.h"

int main (int argc, char**args)
{
   
    Engine::GetInstance()->init();
    while (Engine::GetInstance()->isRuning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }
    
    Engine::GetInstance()->clean();
    Engine::GetInstance()->Quit();
    return 0;
}
