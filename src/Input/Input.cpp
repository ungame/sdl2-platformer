#include <SDL2/SDL.h>
#include "Input.hpp"

Input* Input::_input = nullptr;

Input::Input()
{
    _keyboard = SDL_GetKeyboardState(nullptr);
    _mouseButton = 0;
    _cursor = { 0, 0 };
}

bool Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
            _keyboard = SDL_GetKeyboardState(nullptr);
            break;

        case SDL_MOUSEBUTTONDOWN:
            _mouseButton = event.button.button;
            break;

        case SDL_MOUSEBUTTONUP:
            _mouseButton = 0;

        case SDL_MOUSEMOTION:
            _cursor.x = event.motion.x;
            _cursor.y = event.motion.y;
            break;

        default:
            break;
        }
    }

    return true;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
    return _keyboard[key] == 1;
}

bool Input::IsMouseButtonDown(MouseButton mouseButton)
{
    if(mouseButton == MouseButton::LEFT)
        return _mouseButton == SDL_BUTTON_LEFT;
    return _mouseButton == SDL_BUTTON_RIGHT;
}
