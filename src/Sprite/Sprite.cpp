#include <vector>
#include <SDL2/SDL.h>

#include "Sprite.hpp"

Sprite::Sprite(int frameWidth, int frameHeight)
{
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;
}

Sprite::Sprite(int frameWidth, int frameHeight, int row, int frames)
{
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;

    for(int i = 0; i < frames; i++)
    {
        SDL_Rect frame = { frameWidth * i, frameHeight * row, frameWidth, frameHeight };
        _frames.push_back(frame);
    }
}

void Sprite::AddFrame(int row, int frameIndex)
{
    SDL_Rect frame = { _frameWidth * frameIndex, _frameHeight * row, _frameWidth, _frameHeight };
    _frames.push_back(frame);
}

SDL_Rect Sprite::GetFrame(int frameIndex)
{
    if(frameIndex >= Size())
        return SDL_Rect{};

    return _frames[frameIndex];
}
