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
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

Slider::Slider(int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mousedrag", this, (EventRecieverMethod) &Slider::_onDrag);
    _imageList.addImage("art/intrface/prfsldon.frm");
    _imageList.addImage("art/intrface/prfsldof.frm");
}

Slider::~Slider()
{
}

void Slider::_onDrag(MouseEvent* event)
{
    //auto newOffset = xOffset() + event->xOffset();
    //if (newOffset <= 218 && newOffset >= 0)
    {
        //setXOffset(newOffset);
        //_value = ((maxValue() - minValue())/218)*xOffset();
    }
}

Texture* Slider::texture()
{
    if (_drag) return _imageList.images()->at(0)->texture();
    return _imageList.images()->at(1)->texture();
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
    //_xOffset = (218/(maxValue() - minValue())) * _value;
}

}
