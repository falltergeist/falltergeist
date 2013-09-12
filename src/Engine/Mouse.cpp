#include "../Engine/Mouse.h"
#include "../Engine/ResourceManager.h"
#include <iostream>

namespace Falltergeist
{

Mouse::Mouse()
{
    loadFromSurface(ResourceManager::surface("art/intrface/actarrow.frm"));
    // Hide cursor
    SDL_ShowCursor(0);
}

Surface * Mouse::think()
{
    SDL_GetMouseState(&_x, &_y);
    return this;

}

Mouse::~Mouse()
{
    // Show cursor
    SDL_ShowCursor(1);
}

}
