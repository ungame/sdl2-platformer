#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <SDL2/SDL.h>

#include "Time.hpp"
#include "Sprite.hpp"

class Animation
{
    public:
        Animation(std::string name, Sprite* sprite, double frameInterval, bool repeat);
        SDL_Rect Next();
        bool IsFinished();
        void Reset();

    public:
        inline std::string GetName() { return _name; }

    private:
        Sprite* _sprite;
        std::string _name;
        int _currentFrame;
        bool _isStarted;
        double _frameInterval;
        Time* _frameStartedAt;
        bool _repeat;
        bool _hasCompleted;

    private:
        void next();      
};

#endif