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

// Related headers
#include "../UI/MonthCounter.h"

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Texture.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
using namespace std;

namespace UI
{

enum
{
    MONTH_TEXTURE_WIDTH  = 28,
    MONTH_TEXTURE_HEIGHT = 14,
    MONTH_TEXTURE_HORIZONTAL_OFFSET = 15
};

MonthCounter::MonthCounter(Month month, const Point& pos) : Base(pos), _month(month)
{
    _sprite = make_shared<Graphics::Sprite>("art/intrface/months.frm");

    for (auto i = 0; i<12; i++)
    {
        _rects.push_back({0,i*15,29,14});
    }
    _size = Size(29,14);
}

MonthCounter::MonthCounter(const Point& pos) : MonthCounter(Month::JANUARY, pos)
{
}

MonthCounter::Month MonthCounter::month() const
{
    return _month;
}

void MonthCounter::setMonth(Month month)
{
    _month = month;
}

bool MonthCounter::opaque(const Point &pos)
{
    if (pos.x() > _size.width() || pos.x()<0 || pos.y() > _size.height() || pos.y()<0)
    {
        return false;
    }

    SDL_Rect rect = _rects.at(_month);
    return _sprite->opaque(pos.x()+rect.x, pos.y()+rect.y);
}

void MonthCounter::render(bool eggTransparency)
{
    SDL_Rect rect = _rects.at(_month);
    _sprite->renderCropped(position().x(), position().y(), rect.x, rect.y, rect.w, rect.h);
}

}
}
