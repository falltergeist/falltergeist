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
#include "../UI/Image.h"
#include "../UI/Slider.h"

// Third party includes

namespace Falltergeist
{

Slider::Slider(int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mousedrag", [this](Event* event){ this->_onDrag(dynamic_cast<MouseEvent*>(event)); });
    _imageList.addImage("art/intrface/prfsldon.frm");
    _imageList.addImage("art/intrface/prfsldof.frm");
}

Slider::~Slider()
{
}

void Slider::handle(Event* event)
{
    if(auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        if (!texture()) return;

        int x = mouseEvent->x() - _x;
        int y = mouseEvent->y() - _y;

        //if we are in slider coordinates and not on thumb (slider size = 218 + thumb size, thumb size = 21)
        if (x > 0 && x < 239 && y > 0 && y < this->height() && !this->pixel(mouseEvent->x() - _xOffset, mouseEvent->y() - _yOffset))
        {
            //on left button up only when not dragging thumb
            if (mouseEvent->name() == "mouseup" && mouseEvent->leftButton() && !_drag)
            {
                x -= 10; //~middle of thumb
                if (x < 0) x = 0;
                if (x > 218) x = 218;
                _xOffset = x;
                _value = ((maxValue() - minValue())/218)*_xOffset;
                return;
            }
        }
    }
    //pass it to default handler
    ActiveUI::handle(event);
}

void Slider::_onDrag(MouseEvent* event)
{
    auto sender = dynamic_cast<Slider*>(event->emitter());
    auto newOffset = sender->_xOffset + event->xOffset();
    if (newOffset <= 218 && newOffset >= 0)
    {
        sender->_xOffset = newOffset;
        sender->_value = ((sender->maxValue() - sender->minValue())/218)*sender->_xOffset;
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
    _xOffset = (218/(maxValue() - minValue())) * _value;
}

int Slider::x()
{
    return _x + _xOffset;
}

}
