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

#ifndef FALLTERGEIST_UI_ANIMATIONFRAME_H
#define FALLTERGEIST_UI_ANIMATIONFRAME_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

using Graphics::Point;
using Graphics::Size;

class AnimationFrame
{
public:
    AnimationFrame();
    ~AnimationFrame();
    
    Point position() const;
    void setPosition(const Point&);

    unsigned int x() const;
    unsigned int y() const;
    
    
    Size size() const;
    void setSize(const Size&);
    
    unsigned int width() const;
    unsigned int height() const;
    
    Point offset() const;
    void setOffset(const Point&);

    int xOffset() const;
    int yOffset() const;
    
    unsigned int duration() const;
    void setDuration(unsigned int duration);

protected:
    // Offset of animation frame position relative to sprite position
    Point _position;

    // Animation frame width and height
    Size _size;

    // Offset of animation frame on screen relative to first animation frame
    Point _offset;

    // Duration of animation frame in milliseconds
    unsigned int _duration = 0;
};

}
}
#endif // FALLTERGEIST_UI_ANIMATIONFRAME_H
