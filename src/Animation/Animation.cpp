#include <string>
#include <SDL2/SDL.h>

#include "Time.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"

Animation::Animation(std::string name, Sprite* sprite, double frameInterval, bool repeat)
{
    _name = name;
    _sprite = sprite;
    _currentFrame = 0;
    _isStarted = false;
    _frameInterval = frameInterval;
    _frameStartedAt = nullptr;
    _repeat = repeat;
}

SDL_Rect Animation::Next()
{
    if(!_isStarted)
    {
        _isStarted = true;
        _frameStartedAt = new Time();
    }

    // if(_name == "jumping")
    //     SDL_Log("Animation: %s, CurrentFrame=%d, Frames=%d, Elapsed=%lf", _name.c_str(), _currentFrame, _sprite->Size(), Time::Since(_frameStartedAt));

    SDL_Rect frame = _sprite->GetFrame(_currentFrame);

    next();

    return frame;
}

void Animation::next()
{
    double elapsed = Time::Since(_frameStartedAt);
    
    if(elapsed < _frameInterval)
        return;

    if(_currentFrame == _sprite->Size() - 1)
    {
        if(_repeat)
            _currentFrame = 0;
    }
    else
    {
        _currentFrame++;
    }

    _frameStartedAt = new Time();
}

bool Animation::IsFinished()
{
    return _currentFrame == _sprite->Size() -1 && Time::Since(_frameStartedAt) >= _frameInterval;
}

void Animation::Reset()
{
    _isStarted = false;
    _currentFrame = 0;
    _frameStartedAt = nullptr;
}
