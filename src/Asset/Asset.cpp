#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Asset.hpp"

Asset::Asset(SDL_Renderer* renderer, std::string filepath)
{
    _width = 0;
    _height = 0;

    SDL_Surface* surface = IMG_Load(filepath.c_str());

    if(surface == nullptr) 
    {
        _error = std::string(IMG_GetError());
        return;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(_texture == nullptr)
    {
        _error = std::string(SDL_GetError());
        return;
    }

    SDL_FreeSurface(surface);

    _width = surface->w;
    _height = surface->h;
}

void Asset::Draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale, SDL_RendererFlip flip)
{
    SDL_Rect src;
    src.x = width * frame;
    src.y = height * row;
    src.w = width;
    src.h = height;

    Draw(renderer, &src, x, y, scale, flip);
}

void Asset::Draw(SDL_Renderer* renderer, SDL_Rect* frame, int x, int y, int scale, SDL_RendererFlip flip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = frame->w * scale;
    dst.h = frame->h * scale;

    // SDL_Log("Draw: src{X=%d, Y=%d, W=%d, H=%d}, dst{X=%d, Y=%d, W=%d, H=%d}, Scale=%d", frame->x, frame->y, frame->w, frame->h, dst.x, dst.y, dst.w, dst.h, scale);

    double angle = 0;
    SDL_Point* center = nullptr;

    if(SDL_RenderCopyEx(renderer, _texture, frame, &dst, angle, center, flip) != 0)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on sdl render copy ex: %s", SDL_GetError());

}

void Asset::Destroy()
{
    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);
} 