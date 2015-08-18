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

void AnimationFrame::setX(unsigned int x)
{
    _x = x;
}

unsigned int AnimationFrame::x() const
{
    return _x;
}

void AnimationFrame::setY(unsigned int y)
{
    _y = y;
}

unsigned int AnimationFrame::y() const
{
    return _y;
}

void AnimationFrame::setWidth(unsigned int width)
{
    _width = width;
}

unsigned int AnimationFrame::width() const
{
    return _width;
}

void AnimationFrame::setHeight(unsigned int height)
{
    _height = height;
}

unsigned int AnimationFrame::height() const
{
    return _height;
}

void AnimationFrame::setXOffset(unsigned int xOffset)
{
    _xOffset = xOffset;
}

unsigned int AnimationFrame::xOffset() const
{
    return _xOffset;
}

void AnimationFrame::setYOffset(unsigned int yOffset)
{
    _yOffset = yOffset;
}

unsigned int AnimationFrame::yOffset() const
{
    return _yOffset;
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
