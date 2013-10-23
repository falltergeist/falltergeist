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

ImageButton::ImageButton(std::string releasedImage, std::string pressedImage, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _releasedImage = releasedImage;
    _pressedImage = pressedImage;
    setNeedRedraw(true);
    onMouseIn((EventHandler) &ImageButton::mouseInHandler);
    onMouseOut((EventHandler) &ImageButton::mouseOutHandler);
    onLeftButtonPress((EventHandler) &ImageButton::mouseUpHandler);
    onLeftButtonRelease((EventHandler) &ImageButton::mouseDownHandler);
}

ImageButton::ImageButton(unsigned int type, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    switch (type)
    {
        case BUTTON_SMALL_RED_CIRCLE:
            _pressedImage  = "art/intrface/lilreddn.frm";
            _releasedImage = "art/intrface/lilredup.frm";
            break;
        case BUTTON_BIG_RED_CIRCLE:
            _pressedImage  = "art/intrface/menudown.frm";
            _releasedImage = "art/intrface/menuup.frm";
            break;
        case BUTTON_SKILL_TOGGLE:
            _pressedImage  = "art/intrface/tgsklon.frm";
            _releasedImage = "art/intrface/tgskloff.frm";
            break;
        case BUTTON_PLUS:
            _pressedImage  = "art/intrface/splson.frm";
            _releasedImage = "art/intrface/splsoff.frm";
            break;
        case BUTTON_MINUS:
            _pressedImage  = "art/intrface/snegon.frm";
            _releasedImage = "art/intrface/snegoff.frm";
            break;
        case BUTTON_LEFT_ARROW:
            _pressedImage  = "art/intrface/sld.frm";
            _releasedImage = "art/intrface/slu.frm";
            break;
        case BUTTON_RIGHT_ARROW:
            _pressedImage  = "art/intrface/srd.frm";
            _releasedImage = "art/intrface/sru.frm";
            break;
    }

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

void ImageButton::setPressedImage(std::string pressedImage)
{
    _pressedImage = pressedImage;
}

void ImageButton::setReleasedImage(std::string releasedImage)
{
    _releasedImage = releasedImage;
}

}
