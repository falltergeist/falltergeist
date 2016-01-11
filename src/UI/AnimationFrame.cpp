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
#include "../UI/AnimationFrame.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace UI
{

AnimationFrame::AnimationFrame()
{
}

AnimationFrame::~AnimationFrame()
{
}

Point AnimationFrame::position() const
{
    return _position;
}

void AnimationFrame::setPosition(const Point& pos)
{
    _position = pos;
}

unsigned int AnimationFrame::x() const
{
    return _position.x();
}

unsigned int AnimationFrame::y() const
{
    return _position.y();
}

Size AnimationFrame::size() const
{
    return _size;
}

void AnimationFrame::setSize(const Size& size)
{
    _size = size;
}

unsigned int AnimationFrame::width() const
{
    return _size.width();
}

unsigned int AnimationFrame::height() const
{
    return _size.height();
}

Point AnimationFrame::offset() const
{
    return _offset;
}

void AnimationFrame::setOffset(const Point& ofs)
{
    _offset = ofs;
}

int AnimationFrame::xOffset() const
{
    return _offset.x();
}

int AnimationFrame::yOffset() const
{
    return _offset.y();
}

void AnimationFrame::setDuration(unsigned int duration)
{
    _duration = duration;
}

unsigned int AnimationFrame::duration() const
{
    return _duration;
}

}
}
