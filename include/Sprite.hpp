#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <SDL2/SDL.h>

class Sprite
{
    public:
        Sprite(int frameWidth, int frameHeight);
        Sprite(int frameWidth, int frameHeight, int rows, int frames);
        void AddFrame(int row, int frameIndex);
        SDL_Rect GetFrame(int index);

    public:
        inline int Size() { return _frames.size(); }
        inline void Destroy() { _frames.clear(); }

    private:
        std::vector<SDL_Rect> _frames;
        int _frameWidth;
        int _frameHeight;
};

#endif