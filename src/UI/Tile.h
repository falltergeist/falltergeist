/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_UI_TILE_H
#define FALLTERGEIST_UI_TILE_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Graphics/Point.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{
    class Texture;
}

namespace UI
{

using Graphics::Point;

class Tile
{
public:
    Tile(unsigned int number, const Point &pos);

    unsigned int number() const;

    Point position() const;

    unsigned int index() const;
    void setIndex(unsigned int value);
    void enable();
    void disable();
    bool enabled();


protected:
    unsigned int _index = 0;
    unsigned int _number = 0;
    Point _position;
    bool _enabled = true;
};

}
}
#endif // FALLTERGEIST_UI_TILE_H
