/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Mouse.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/ResourceManager.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

Mouse::Mouse()
{
    // Hide cursor
    SDL_ShowCursor(0);

    auto frm = ResourceManager::frmFileType("art/intrface/stdarrow.frm");
    auto pal = ResourceManager::palFileType("color.pal");

    _texture = new Texture(frm->width(), frm->height());
    _texture->loadFromRGBA(frm->rgba(pal));
}

Mouse::~Mouse()
{
    // Show cursor
    SDL_ShowCursor(1);
    delete _texture;
}

void Mouse::think()
{
    SDL_GetMouseState(&_x, &_y);
}

int Mouse::x()
{
    return _x;
}

int Mouse::y()
{
    return _y;
}

void Mouse::setX(int x)
{
    _x = x;
    SDL_WarpMouse(_x, _y);
}

void Mouse::setY(int y)
{
    _y = y;
    SDL_WarpMouse(_x, _y);
}

bool Mouse::visible()
{
    return _visible;
}

void Mouse::setVisible(bool value)
{
    _visible = value;
}

Texture* Mouse::texture()
{
    return _texture;
}

}
