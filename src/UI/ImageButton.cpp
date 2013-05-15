/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#include "../UI/ImageButton.h"
#include "../Engine/ResourceManager.h"

namespace Falltergeist
{

ImageButton::ImageButton(const char * releasedImage, const char * pressedImage, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _releasedImage = (char*)releasedImage;
    _pressedImage = (char*)pressedImage;
    needRedraw(true);
}

ImageButton * ImageButton::draw()
{
    if (!needRedraw()) return this;

    InteractiveSurface::draw();

    int x = this->x();
    int y = this->y();
    if (_hovered && _leftButtonPressed)
    {
        loadFromSurface(ResourceManager::surface(_pressedImage));

    }
    else
    {
        loadFromSurface(ResourceManager::surface(_releasedImage));
    }
    this->x(x);
    this->y(y);
    return this;
}

void ImageButton::setPressedImage(const char * pressedImage)
{
    _pressedImage = (char*)pressedImage;
}

void ImageButton::setReleasedImage(const char * releasedImage)
{
    _releasedImage = (char*)releasedImage;
}

}
