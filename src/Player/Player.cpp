#include <SDL2/SDL.h>

#include "Asset.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Input.hpp"

Player::Player(Asset* asset, SDL_FPoint position)
{
    _asset = asset;    
    _scale = 3;
    _flip = SDL_FLIP_NONE;

    _isJumping = false;
    _isFalling = false;
    _isLanding = false;

    _isAttacking1 = false;
    _isAttacking2 = false;

    _ground = position.y;
    _isOnTheGround = true;

    int frameWidth = asset->GetWidth() / 10;
    int frameHeight = (asset->GetHeight() / 12);

    _width = frameWidth;
    _height = frameHeight;
    _jumpForce = PLAYER_JUMP_FORCE;

    _object = new Object("player", position.x, position.y - (frameHeight * _scale));

    Sprite* spriteIdle = new Sprite(frameWidth, frameHeight);
    spriteIdle->AddFrame(0, 0);
    spriteIdle->AddFrame(0, 1);
    spriteIdle->AddFrame(0, 2);
    spriteIdle->AddFrame(0, 3);

    double frameInterval = 0.1;
    bool repeat = true;
    Animation* idle = new Animation("idle", spriteIdle, frameInterval, repeat);

    _object->AddAnimation(idle->GetName(), idle);

    _currentAnimation = idle->GetName();

    Sprite* spriteRunning = new Sprite(frameWidth, frameHeight);
    spriteRunning->AddFrame(1, 0);
    spriteRunning->AddFrame(1, 1);
    spriteRunning->AddFrame(1, 2);
    spriteRunning->AddFrame(1, 3);
    spriteRunning->AddFrame(1, 4);
    spriteRunning->AddFrame(1, 5);

    frameInterval = 0.1;
    Animation* running = new Animation("running", spriteRunning, frameInterval, repeat);

    _object->AddAnimation(running->GetName(), running);

    Sprite* spriteJumping = new Sprite(frameWidth, frameHeight);
    spriteJumping->AddFrame(2, 0);
    spriteJumping->AddFrame(2, 1);
    spriteJumping->AddFrame(2, 2);
    spriteJumping->AddFrame(2, 3);
    spriteJumping->AddFrame(2, 4);

    frameInterval = 0.1;
    Animation* jumping = new Animation("jumping", spriteJumping, frameInterval, false);

    _object->AddAnimation(jumping->GetName(), jumping);
    Sprite* spriteFalling = new Sprite(frameWidth, frameHeight);
    spriteFalling->AddFrame(2, 5);
    spriteFalling->AddFrame(2, 6);
    spriteFalling->AddFrame(2, 7);

   Animation* falling = new Animation("falling", spriteFalling, frameInterval, true);

    _object->AddAnimation(falling->GetName(), falling);

    Sprite* spriteLanding = new Sprite(frameWidth, frameHeight);
    spriteLanding->AddFrame(2, 8);
    spriteLanding->AddFrame(2, 9);

    frameInterval = 0.15;
    Animation* landing = new Animation("landing", spriteLanding, frameInterval, false);

    _object->AddAnimation(landing->GetName(), landing);

    Sprite* spriteAttack1 = new Sprite(frameWidth, frameHeight, 4, 10);
    Animation* attack1 = new Animation("attack1", spriteAttack1, 0.1, false);
    _object->AddAnimation(attack1->GetName(), attack1);

    Sprite* spriteAttack2 = new Sprite(frameWidth, frameHeight, 5, 10);
    Animation* attack2 = new Animation("attack2", spriteAttack2, 0.1, false);
    _object->AddAnimation(attack2->GetName(), attack2);
}

void Player::Update(float deltaTime)
{
    if(Input::Instance()->IsMouseButtonDown(MouseButton::LEFT) && _isOnTheGround && !_isLanding)
    {
        _isAttacking1 = true;
        _isAttacking2 = false;
    }

    if(Input::Instance()->IsMouseButtonDown(MouseButton::RIGHT) && _isOnTheGround && !_isLanding)
    {
        _isAttacking1 = false;
        _isAttacking2 = true;
    }

    bool isAttacking = _isAttacking1 || _isAttacking2;

    float boost = 1.0F;

    bool isJump = Input::Instance()->IsKeyDown(SDL_SCANCODE_UP) || Input::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) || Input::Instance()->IsKeyDown(SDL_SCANCODE_W);

    if(isJump && _isOnTheGround && !_isLanding)
    {
        _isOnTheGround = false;
        _isJumping = true;
    }
  
    _lastPosition = _object->GetPostion();

    if(!_isOnTheGround)
    {
        SDL_FPoint position = _object->GetPostion();

        float y = position.y - (_jumpForce * deltaTime);
        _object->SetY(y);
        _jumpForce -= (GRAVITY  * deltaTime);

        if(_lastPosition.y < y)
        {
            _isJumping = false;
            _isFalling = true;
        }
        else
        {
            float yh = _object->GetPostion().y + _height;
            float yhs = _object->GetPostion().y + (_height * _scale);
            SDL_Log("Jumping: W=%d, H=%d, Y=%f, Y+H=%f, Y+(H*S)=%f Ground=%d", _width, _height, _object->GetPostion().y, yh, yhs, _ground);
        }

        boost = 2.0f;   
    }

    if(_isFalling)
    {
        float yh = _object->GetPostion().y + _height;
        float yhs =_object->GetPostion().y + (_height * _scale);
        SDL_Log("Jumping: W=%d, H=%d, Y=%f, Y+H=%f, Y+(H*S)=%f Ground=%d", _width, _height, _object->GetPostion().y, yh, yhs, _ground);
    }

    _isWalking = false;

    bool isWalkingRight = Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_D);

    float xSpeed = PLAYER_WALK_SPEED * boost;
    SDL_FPoint position = _object->GetPostion();

    if(isWalkingRight && !_isLanding && !isAttacking)
    {
        float x = position.x + (xSpeed * deltaTime);
        _object->SetX(x);
        _isWalking = _isOnTheGround;
        _flip = SDL_FLIP_NONE;
    }

    bool isWalkingLeft = Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_A);

    if(isWalkingLeft && !_isLanding && !isAttacking)
    {
        float x = position.x - (xSpeed * deltaTime);
        _object->SetX(x);
        _isWalking = _isOnTheGround;
        _flip = SDL_FLIP_HORIZONTAL;
    }

    if(position.y + (_height * _scale) >= _ground)
    {
        if(!_isLanding && _isFalling)
            _isLanding = true;

        float y = _ground - (_height * _scale);
        _object->SetY(y);
        _isOnTheGround = true;
        _isJumping = false;
        _isFalling = false;
        _jumpForce = PLAYER_JUMP_FORCE;
    }

    if(_isLanding && _object->GetAnimation(_currentAnimation)->IsFinished())
        _isLanding = false;

    if((_isAttacking1 || _isAttacking2) && _object->GetAnimation(_currentAnimation)->IsFinished())
    {
         _isAttacking1 = false;
         _isAttacking2 = false;
    }

    animate();
}

void Player::animate()
{
    if(_isWalking)
    {
        if(_currentAnimation == "idle")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "running";
        }
    }
    else if(_isJumping)
    {
        if(_currentAnimation != "jumping")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "jumping";
        }
    }
    else if (_isFalling)
    {
        if(_currentAnimation != "falling")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "falling";
        }
    }
    else if(_isLanding)
    {
        if(_currentAnimation != "landing")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "landing";
        }
    }
    else if(_isAttacking1)
    {
        if(_currentAnimation != "attack1")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "attack1"; 
        }
    }
    else if(_isAttacking2)
    {
        if(_currentAnimation != "attack2")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "attack2"; 
        }
    }
    else
    {
        if(_currentAnimation != "idle")
        {
            _object->GetAnimation(_currentAnimation)->Reset();
            _currentAnimation = "idle"; 
        }
    }
}

void Player::Draw(SDL_Renderer* renderer)
{
    SDL_Rect frame = _object->GetAnimation(_currentAnimation)->Next();
    SDL_FPoint position = _object->GetPostion();

    _asset->Draw(renderer, &frame, position.x, position.y, _scale, _flip);
}
