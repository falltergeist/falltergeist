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

#ifndef FALLTERGEIST_UI_ANIMATIONFRAME_H
#define FALLTERGEIST_UI_ANIMATIONFRAME_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace UI
{

class AnimationFrame
{
public:
    AnimationFrame();
    ~AnimationFrame();

    unsigned int x() const;
    void setX(unsigned int x);

    unsigned int y() const;
    void setY(unsigned int y);

    unsigned int width() const;
    void setWidth(unsigned int width);

    unsigned int height() const;
    void setHeight(unsigned int height);

    int xOffset() const;
    void setXOffset(int xOffset);

    int yOffset() const;
    void setYOffset(int yOffset);

    unsigned int duration() const;
    void setDuration(unsigned int duration);

protected:
    // Offset of animation frame position relative to sprite position
    unsigned int _x = 0;
    unsigned int _y = 0;

    // Animation frame width and height
    unsigned int _height = 0;
    unsigned int _width = 0;

    // Offset of animation frame on screen relative to first animation frame
    int _xOffset = 0;
    int _yOffset = 0;

    // Duration of animation frame in milliseconds
    unsigned int _duration = 0;
};

}
}
#endif // FALLTERGEIST_UI_ANIMATIONFRAME_H
