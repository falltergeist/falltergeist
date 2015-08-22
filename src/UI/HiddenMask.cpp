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

// Related headeres
#include "../UI/HiddenMask.h"

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

HiddenMask::HiddenMask(unsigned int width, unsigned int height, int x, int y) : Image(width, height)
{
    setPosition({x, y});
}

HiddenMask::~HiddenMask()
{
}

unsigned int HiddenMask::pixel(unsigned int x, unsigned int y)
{
    if (x > width())  return 0;
    if (y > height()) return 0;

    return 0xffffffff;
}

void HiddenMask::render(bool eggTransparency)
{
}

void HiddenMask::think()
{
}

}
}
