#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <SDL2/SDL.h>

#include "Asset.hpp"
#include "Object.hpp"

#define PLAYER_WALK_SPEED 3.0f
#define PLAYER_JUMP_FORCE 20.0f
#define GRAVITY 1.0f

class Player
{
    public:
        Player(Asset* asset, SDL_FPoint position);
        void Update(float deltaTime);
        void Draw(SDL_Renderer* renderer);

    public:
        inline void Destroy() { _asset->Destroy(); }

    private:
        Asset* _asset;
        Object* _object;
        SDL_RendererFlip _flip;
        int _scale;
        int _width;
        int _height;
        SDL_FPoint _lastPosition;

    private:
        std::string _currentAnimation;
        bool _isWalking;
        bool _isJumping;
        float _jumpForce;
        bool _isOnTheGround;
        int _ground;
        bool _isFalling;
        bool _isLanding;
        bool _isAttacking1;
        bool _isAttacking2;

        void animate();
};

#endif