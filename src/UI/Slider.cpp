/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../UI/Slider.h"

// Third party includes

namespace Falltergeist
{

Slider::Slider(int x, int y) : InteractiveSurface(0, 0, x, y)
{
    addEventHandler("mousedrag", this, (EventRecieverMethod) &Slider::_onDrag);
    _surfaceSet.addSurface(new Surface(ResourceManager::surface("art/intrface/prfsldon.frm")));
    _surfaceSet.addSurface(new Surface(ResourceManager::surface("art/intrface/prfsldof.frm")));
}

Slider::~Slider()
{
}

void Slider::_onDrag(MouseEvent* event)
{
    auto newOffset = xOffset() + event->xOffset();
    if (newOffset <= 218 && newOffset >= 0)
    {
        setXOffset(newOffset);
        _value = ((maxValue() - minValue())/218)*xOffset();
    }
}

SDL_Surface* Slider::sdl_surface()
{
    if (_drag) return _surfaceSet.surfaces()->at(0)->sdl_surface();
    return _surfaceSet.surfaces()->at(1)->sdl_surface();
}

double Slider::minValue()
{
    return _minValue;
}

void Slider::setMinValue(double value)
{
    _minValue = value;
}

double Slider::maxValue()
{
    return _maxValue;
}

void Slider::setMaxValue(double value)
{
    _maxValue = value;
}

double Slider::value()
{
    return _value;
}

void Slider::setValue(double value)
{
    _value = value;
    _xOffset = (218/(maxValue() - minValue())) * _value;
}

}
