#include <string>
#include "SDL2/SDL.h"

#include "Asset.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Slime.hpp"

Slime::Slime(Asset* asset, SDL_FPoint position)
{
    _scale = 3;
    _flip = SDL_FLIP_NONE;
    _asset = asset;

    int frameWidth = asset->GetWidth() / 8;
    int frameHeight = asset->GetHeight() / 3;

    int x = position.x - (frameWidth * _scale);
    int y =  position.y - (frameHeight * _scale);
    
    _object = new Object("slime", x, y);

    Sprite* spriteIdle = new Sprite(frameWidth, frameHeight);
    spriteIdle->AddFrame(0, 0);
    spriteIdle->AddFrame(0, 1);
    spriteIdle->AddFrame(0, 2);
    spriteIdle->AddFrame(0, 3);

    double frameInterval = 0.2; // 200ms
    bool repeat = true;
    Animation* idle = new Animation("idle", spriteIdle, frameInterval, repeat);

    _object->AddAnimation(idle->GetName(), idle);
}

void Slime::Update(float deltaTime)
{

}

void Slime::Draw(SDL_Renderer* renderer)
{
    SDL_Rect frame = _object->GetAnimation("idle")->Next();
    SDL_FPoint position = _object->GetPostion();
    _asset->Draw(renderer, &frame, position.x, position.y, _scale, _flip);
}