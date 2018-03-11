/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#include <utility>

#include "../UI/Rectangle.h"

#include "../Game/Game.h"
#include "../Graphics/Renderer.h"

namespace Falltergeist
{
namespace UI
{

Rectangle::Rectangle(const Point &pos, Size size, SDL_Color color) : Base(pos), _size(std::move(size)), _color(std::move(color))
{
}

void Rectangle::render(bool eggTransparency)
{
    Game::getInstance()->renderer()->drawRect(position(),_size, _color);
}

bool Rectangle::opaque(unsigned int x, unsigned int y)
{
    return false;
}

bool Rectangle::opaque(const Point &pos)
{
    return false;
}

Size Rectangle::size() const
{
    return _size;
}

}
}
