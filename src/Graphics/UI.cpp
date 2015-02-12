/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include <algorithm>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Graphics/UI.h"
#include "../ResourceManager.h"

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
    // Delete texture only if it wasn't allocated by Resource Manager
    if (_texture)
    {
        bool found = false;
        for (auto it = ResourceManager::textures()->begin(); it != ResourceManager::textures()->end(); ++it)
        {
            if (it->second == _texture)
            {
                found = true;
                break;
            }
        }
        if (!found) delete _texture;
    }
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

void UI::render()
{
    Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
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

unsigned int UI::width()
{
    if (!texture()) return 0;
    return texture()->width();
}

unsigned int UI::height()
{
    if (!texture()) return 0;
    return texture()->height();
}

unsigned int UI::pixel(unsigned int x, unsigned int y)
{
    return texture() ? texture()->pixel(x, y) : 0;
}

}
