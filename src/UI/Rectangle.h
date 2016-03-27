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

#ifndef FALLTERGEIST_UI_RECTANGLE_H
#define FALLTERGEIST_UI_RECTANGLE_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../UI/Base.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{
namespace UI
{

class Rectangle : public Base
{
public:

    Rectangle(const Point& pos, const Size& size, SDL_Color color);
    virtual void render(bool eggTransparency = false) override;

    bool opaque(unsigned int x, unsigned int y);
    virtual bool opaque(const Point &pos) override;

    virtual Size size() const override;

private:
    Size _size;
    SDL_Color _color;
};

}
}
#endif //FALLTERGEIST_UI_RECTANGLE_H
