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
#include "../UI/TextAreaList.h"

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Rect.h"
#include "../UI/TextArea.h"


// Third party includes

namespace Falltergeist
{

namespace UI
{


TextAreaList::TextAreaList(const Point &pos) : Falltergeist::UI::Base(pos)
{

}

TextAreaList::~TextAreaList()
{

}


void  TextAreaList::setSize(Size size)
{
    _size=size;
}


void TextAreaList::addArea(std::unique_ptr<TextArea> area)
{
    _areas.push_back(std::move(area));
    _recalculatePositions();
}

const std::vector<std::unique_ptr<TextArea>> &TextAreaList::textAreas() const
{
    return _areas;
}

bool TextAreaList::opaque(const Point &pos)
{
    return Graphics::Rect::inRect(pos, this->size());

}

void TextAreaList::render(bool eggTransparency)
{
    for (unsigned int i = 0; i < _visibleCount; i++)
    {
        _areas.at(_areaIndex+i)->render(eggTransparency);
    }
}


void TextAreaList::scrollTo(int index)
{
    _areaIndex=index;
    if (_areaIndex >= static_cast<int>(_areas.size()))
    {
        _areaIndex = static_cast<int>(_areas.size());
    }
    if (_areaIndex < 0)
    {
        _areaIndex = 0;
    }
    _recalculatePositions();
}


void TextAreaList::scrollDown(int count)
{
    if (_areaIndex+count>=(int)_areas.size())
    {
        return;
    }
    _areaIndex+=count;
    _recalculatePositions();
}

void TextAreaList::scrollUp(int count)
{
    if (_areaIndex-count<0)
    {
        return;
    }
    _areaIndex-=count;
    _recalculatePositions();
}

void TextAreaList::_recalculatePositions()
{
    _totalHeight = 0;
    _visibleCount = 0;
    for (unsigned int i = _areaIndex; i < _areas.size(); i++)
    {
        _areas.at(i)->setPosition(position()+Size(0,_totalHeight));
        _totalHeight+=_areas.at(i)->textSize().height()+_areas.at(i)->font()->verticalGap()*2;

        if (_totalHeight>_size.height())
        {
            break;
        }
        _visibleCount++;
    }
}


}
}
