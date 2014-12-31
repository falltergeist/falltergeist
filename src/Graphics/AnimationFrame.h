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

#ifndef FALLTERGEIST_ANIMATIONFRAME_H
#define FALLTERGEIST_ANIMATIONFRAME_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

class AnimationFrame
{
protected:
    // Смещение начала кадра анимации относительно начала спрайта
    unsigned int _x = 0;
    unsigned int _y = 0;

    // Высота и ширина кадра анимации
    unsigned int _height = 0;
    unsigned int _width = 0;

    // Смещение кадра анимации на экране относительно первого кадра анимации
    unsigned int _xOffset = 0;
    unsigned int _yOffset = 0;

    // Длительность кадра анимации в милисекундах
    unsigned int _duration = 0;

public:
    AnimationFrame();
    ~AnimationFrame();

    void setX(unsigned int x);
    unsigned int x();

    void setY(unsigned int y);
    unsigned int y();

    void setWidth(unsigned int width);
    unsigned int width();

    void setHeight(unsigned int height);
    unsigned int height();

    void setXOffset(unsigned int xOffset);
    unsigned int xOffset();

    void setYOffset(unsigned int yOffset);
    unsigned int yOffset();

    void setDuration(unsigned int duration);
    unsigned int duration();
};

}
#endif // FALLTERGEIST_ANIMATIONFRAME_H
