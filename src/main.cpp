#include <iostream>
#include <string>

#include "Engine.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[])
{
    if(!Engine::Instance()->Init())
        return EXIT_FAILURE;

    float delay = 0;

    if(argc > 1)
    {
        delay = std::stof(std::string(argv[1]));
        std::cout << "Argv[1]=" << argv[1] << ", Delay=" << delay << std::endl;
    }

    while(Engine::Instance()->IsRunning())
    {
        Engine::Instance()->Update();
        Engine::Instance()->Draw();
        Timer::Instance()->Tick();

        SDL_Delay(delay);
    }

    Engine::Instance()->Quit();
    
    return EXIT_SUCCESS;
}