#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <map>
#include <SDL2/SDL.h>

#include "Asset.hpp"
#include "Animation.hpp"

class Object
{
    public:
        Object(std::string name, float x, float y);

    public:
        inline std::string GetName() { return _name; }

        inline void AddAnimation(std::string name, Animation* animation) { _animations[name] = animation; }
        inline Animation* GetAnimation(std::string name) { return _animations[name]; }

        void SetX(float x) { _position.x = x; }
        void SetY(float y) { _position.y = y; }
        SDL_FPoint GetPostion() { return _position; }

        inline void Destroy() { _animations.clear(); }
        
    private:
        std::string _name;
        std::map<std::string, Animation*> _animations;
        SDL_FPoint _position;
};

#endif