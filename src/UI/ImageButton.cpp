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

// C++ standard includes

// Falltergeist includes
#include "../UI/ImageButton.h"
#include "../Engine/ResourceManager.h"

// Third party includes

namespace Falltergeist
{

ImageButton::ImageButton(const char * releasedImage, const char * pressedImage, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _releasedImage = (char*)releasedImage;
    _pressedImage = (char*)pressedImage;
    setNeedRedraw(true);
    onMouseIn((EventHandler) &ImageButton::mouseInHandler);
    onMouseOut((EventHandler) &ImageButton::mouseOutHandler);
    onLeftButtonPress((EventHandler) &ImageButton::mouseUpHandler);
    onLeftButtonRelease((EventHandler) &ImageButton::mouseDownHandler);
}

void ImageButton::draw()
{
    if (!needRedraw()) return;

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
    this->setX(x);
    this->setY(y);
    this->setXOffset(0);
    this->setYOffset(0);
}

void ImageButton::mouseInHandler(Event * event)
{
    if (_leftButtonPressed && _hovered)
    {
        event->sender()->setNeedRedraw(true);
    }
}

void ImageButton::mouseOutHandler(Event * event)
{
    if (_leftButtonPressed)
    {
        event->sender()->setNeedRedraw(true);
    }
}

void ImageButton::mouseUpHandler(Event * event)
{
    if (_hovered)
    {
        event->sender()->setNeedRedraw(true);
    }
}

void ImageButton::mouseDownHandler(Event * event)
{
    if (_hovered)
    {
        event->sender()->setNeedRedraw(true);
    }
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
