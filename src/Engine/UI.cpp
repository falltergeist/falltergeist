/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/UI.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

UI::UI(int x, int y)
{
    _x = x;
    _y = y;
}

UI::~UI()
{
}

int UI::x()
{
    return _x + _xOffset;
}

void UI::setX(int value)
{
    _x = value;
}

int UI::y()
{
    return _y + _yOffset;
}

void UI::setY(int value)
{
    _y = value;
}

Texture* UI::texture()
{
    return _texture;
}

void UI::setTexture(Texture* texture)
{
    _texture = texture;
}

void UI::think()
{
}

void UI::setVisible(bool value)
{
    _visible = value;
}

bool UI::visible()
{
    return _visible;
}

int UI::xOffset()
{
    return _xOffset;
}

void UI::setXOffset(int xOffset)
{
    _xOffset = xOffset;
}

int UI::yOffset()
{
    return _yOffset;
}

void UI::setYOffset(int yOffset)
{
    _yOffset = yOffset;
}
}
