#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>
#include <SDL2/SDL.h>

class Asset
{
    public:
        Asset(SDL_Renderer* renderer, std::string filepath);
        inline int GetWidth() { return _width; }
        inline int GetHeight() { return _height; }
        inline const char* GetError() { return _error.c_str(); }
        inline bool HasError() { return _error.length() > 0; }

    public:
        void Draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Destroy();

    private:
        SDL_Texture* _texture;
        int _width;
        int _height;
        std::string _error;
};

#endif