#ifndef SLIME_HPP
#define SLIME_HPP

#include <SDL2/SDL.h>
#include "Asset.hpp"
#include "Object.hpp"

class Slime
{
    public:
        Slime(Asset* asset, SDL_FPoint position);
        void Update(float deltaTime);
        void Draw(SDL_Renderer* renderer);

    public:
        inline void Destroy() { _asset->Destroy(); }
        
    private:
        Asset* _asset;
        Object* _object;
        SDL_RendererFlip _flip;
        int _scale; 
};

#endif