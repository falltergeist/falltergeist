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
    setReleasedImage(releasedImage);
    setPressedImage(pressedImage);
}

ImageButton::ImageButton(unsigned int type, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    std::string pressedImage, releasedImage;
    switch (type)
    {
        case BUTTON_SMALL_RED_CIRCLE:
            pressedImage  = "art/intrface/lilreddn.frm";
            releasedImage = "art/intrface/lilredup.frm";
            break;
        case BUTTON_BIG_RED_CIRCLE:
            pressedImage  = "art/intrface/menudown.frm";
            releasedImage = "art/intrface/menuup.frm";
            break;
        case BUTTON_SKILL_TOGGLE:
            pressedImage  = "art/intrface/tgsklon.frm";
            releasedImage = "art/intrface/tgskloff.frm";
            break;
        case BUTTON_PLUS:
            pressedImage  = "art/intrface/splson.frm";
            releasedImage = "art/intrface/splsoff.frm";
            break;
        case BUTTON_MINUS:
            pressedImage  = "art/intrface/snegon.frm";
            releasedImage = "art/intrface/snegoff.frm";
            break;
        case BUTTON_LEFT_ARROW:
            pressedImage  = "art/intrface/sld.frm";
            releasedImage = "art/intrface/slu.frm";
            break;
        case BUTTON_RIGHT_ARROW:
            pressedImage  = "art/intrface/srd.frm";
            releasedImage = "art/intrface/sru.frm";
            break;
        case BUTTON_CHECKBOX:
            releasedImage = "art/intrface/prefxout.frm";
            pressedImage  = "art/intrface/prefxin.frm";
            break;
        default:
            throw Exception("ImageButton::Imagebutton() - wrong button type");
    }
    setReleasedImage(releasedImage);
    setPressedImage(pressedImage);
}

ImageButton::~ImageButton()
{
    delete _releasedSurface;
    delete _pressedSurface;
}

void ImageButton::setSwitchMode(bool mode)
{
    _switchMode = true;
}

bool ImageButton::switchMode()
{
    return _switchMode;
}

void ImageButton::setPressed(bool mode)
{
    _pressed = mode;
}

bool ImageButton::pressed()
{
    if (_switchMode)
    {
        return _pressed;
    }
    if (_hovered && _leftButtonPressed) return true;        
    return false;
}

void ImageButton::setPressedImage(std::string image)
{
    delete _pressedSurface;
    _pressedSurface = new Surface(ResourceManager::surface(image));
    _pressedSurface->setXOffset(0);
    _pressedSurface->setYOffset(0);
}

void ImageButton::setReleasedImage(std::string image)
{
    delete _releasedSurface;
    _releasedSurface = new Surface(ResourceManager::surface(image));
    _releasedSurface->setXOffset(0);
    _releasedSurface->setYOffset(0);
}

SDL_Surface* ImageButton::sdl_surface()
{
    if (pressed()) return _pressedSurface->sdl_surface();

    return _releasedSurface->sdl_surface();
}

void ImageButton::leftButtonClick(Event* event, State* state)
{
    if (switchMode())
    {
        if (pressed())
        {
            setPressed(false);
        }
        else
        {
            setPressed(true);
        }
    }
    InteractiveSurface::leftButtonClick(event, state);
}


}
