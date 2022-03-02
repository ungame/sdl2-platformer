#include <SDL2/SDL.h>

#include "Timer.hpp"

Timer* Timer::_timer = nullptr;

Timer::Timer()
{
    _frameTime = 0;
    _lastFrameTime = 0;
}

void Timer::Tick()
{
    Uint32 tick = SDL_GetTicks();
    _frameTime = tick - _lastFrameTime;
    _lastFrameTime = tick;
}

float Timer::GetDeltaTime()
{
    float deltaTime = _frameTime * (FPS_TARGET / SEC_TO_MS);

    if(deltaTime >= DEFAULT_DELTATIME)
        return DEFAULT_DELTATIME;

    return deltaTime;
}