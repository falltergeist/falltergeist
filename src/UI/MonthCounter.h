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

#ifndef FALLTERGEIST_UI_MONTHCOUNTER_H
#define FALLTERGEIST_UI_MONTHCOUNTER_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Sprite.h"
#include "Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

class Image;

class MonthCounter : public Base
{
public:

    enum Month
    {
        JANUARY = 0,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    MonthCounter(const Point& pos = Point(0, 0));
    MonthCounter(Month month, const Point& pos = Point(0, 0));

    Month month() const;
    void setMonth(Month month);


    virtual bool opaque(const Point &pos) override;


    virtual void render(bool eggTransparency) override;

private:
    Month _month;
    Size _size;
    std::shared_ptr<Graphics::Sprite> _sprite;
    std::vector<SDL_Rect> _rects;
};

}
}
#endif // FALLTERGEIST_UI_MONTHCOUNTER_H
