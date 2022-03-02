#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>

enum MouseButton
{
    NONE,
    LEFT,
    RIGHT
};

class Input
{
    public:
        inline static Input* Instance() { return _input = _input != nullptr ? _input : new Input(); }
        inline SDL_Point GetCursor() { return _cursor; }

    public:
        bool Listen();
        bool IsKeyDown(SDL_Scancode key);
        bool IsMouseButtonDown(MouseButton mouseButton);

    private:
        Input();
        static Input* _input;
        const Uint8* _keyboard;
        Uint8 _mouseButton;
        SDL_Point _cursor;

};

#endif