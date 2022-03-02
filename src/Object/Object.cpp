#include <string>

#include "Asset.hpp"
#include "Object.hpp"

Object::Object(std::string name, float x, float y)
{
    _name = name;
    _position = { x, y };

    SDL_Log("%s: X=%f, Y=%f", name.c_str(), x, y);
}