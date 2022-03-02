#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Asset.hpp"
#include "Player.hpp"
#include "Slime.hpp"

class Engine
{
    public:
        inline static Engine* Instance() { return _engine = _engine != nullptr ? _engine : new Engine(); }
        inline bool IsRunning() { return _isRunning; }
    
    public:
        bool Init();
        void Update();
        void Draw();
        void Quit();

    private:
        Engine();
        static Engine* _engine;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        bool _isRunning;

    private:
        std::string _title;
    
    private:
        Player* _player;
        Slime* _slime;
        
        bool load();
};

#endif