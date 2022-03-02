#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Timer.hpp"
#include "Asset.hpp"
#include "Player.hpp"
#include "Slime.hpp"

Engine* Engine::_engine = nullptr;

Engine::Engine()
{
    _window = nullptr;
    _renderer = nullptr;
    _isRunning = false;
}

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on initialize SDL: %s", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    int imgInitted = IMG_Init(imgFlags);

    if((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on initialize SDL image: %s", IMG_GetError());
        return false;   
    }

    _window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(_window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on create window: %s", SDL_GetError());
        return false;   
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(_renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on create renderer: %s", SDL_GetError());
        return false;   
    }

    SDL_Log("loading assets...");

    _isRunning = load();

    return _isRunning;
}


bool Engine::load()
{
    Asset* player = new Asset(_renderer, "assets/player/player.png");
    
    if(player->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on load player: %s", player->GetError());
        return false;
    }  

    SDL_FPoint position = { 0, WINDOW_HEIGHT };

    _player = new Player(player, position);

    Asset* slime = new Asset(_renderer, "assets/enemy/slime-Sheet.png");
    
    if(slime->HasError())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error on load slime: %s", slime->GetError());
        return false;
    }

    position.x = WINDOW_WIDTH / 2;
    position.y = WINDOW_HEIGHT;

    _slime = new Slime(slime, position);

    return true;
}

void Engine::Update()
{
    _isRunning = Input::Instance()->Listen();

    if(Input::Instance()->IsMouseButtonDown(MouseButton::LEFT))
        SDL_Log("[M-LEFT]");
    if(Input::Instance()->IsMouseButtonDown(MouseButton::RIGHT))
        SDL_Log("[M-RIGHT]");


    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_UP))
        SDL_Log("[UP]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
        SDL_Log("[RIGHT]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
        SDL_Log("[LEFT]");
    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
        SDL_Log("[DOWN]");

    _title = WINDOW_TITLE;
    _title += " | ";

    Time* now = new Time();
    _title += now->String();
    _title += " | ";
    delete now; 

    SDL_Point cursor = Input::Instance()->GetCursor();
    _title += "X=" + std::to_string(cursor.x);
    _title += " | ";
    _title += "Y=" + std::to_string(cursor.y);
    _title += " | ";

    float deltaTime = Timer::Instance()->GetDeltaTime();
    _title += "DeltaTime=" + std::to_string(deltaTime);
    _title += " | ";

    float frameTime = Timer::Instance()->GetFrameTime();
    _title += "FrameTime="+ std::to_string(frameTime);

    _player->Update(deltaTime);
    _slime->Update(deltaTime);
}

void Engine::Draw()
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(_renderer);

    SDL_SetWindowTitle(_window, _title.c_str());

    _player->Draw(_renderer);
    _slime->Draw(_renderer);
  
    SDL_RenderPresent(_renderer);
}

void Engine::Quit()
{
    _player->Destroy();
    _slime->Destroy();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}
