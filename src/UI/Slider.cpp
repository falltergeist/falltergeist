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

// Related headers
#include "../UI/Slider.h"

// C++ standard includes

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Game/Game.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

Slider::Slider(int x, int y) : Falltergeist::UI::Base(x, y)
{
    addEventHandler("mousedrag", [this](Event::Event* event){ this->_onDrag(dynamic_cast<Event::Mouse*>(event)); });
    addEventHandler("mouseleftdown", [this](Event::Event* event){ this->_onLeftButtonDown(dynamic_cast<Event::Mouse*>(event)); });
    addEventHandler("mouseleftup", [this](Event::Event* event){ this->_onLeftButtonUp(dynamic_cast<Event::Mouse*>(event)); });
    _imageList.addImage("art/intrface/prfsldon.frm");
    _imageList.addImage("art/intrface/prfsldof.frm");
    _downSound = "sound/sfx/ib1p1xx1.acm";
    _upSound = "sound/sfx/ib1lu1x1.acm";
}

Slider::~Slider()
{
}

void Slider::handle(Event::Event* event)
{
    if(auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
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
                Game::getInstance()->mixer()->playACMSound(_downSound);
                Game::getInstance()->mixer()->playACMSound(_upSound);
                return;
            }
        }
    }
    //pass it to default handler
    Falltergeist::UI::Base::handle(event);
}

void Slider::_onDrag(Event::Mouse* event)
{
    auto sender = dynamic_cast<Slider*>(event->emitter());
    auto newOffset = sender->_xOffset + event->xOffset();
    if (newOffset <= 218 && newOffset >= 0)
    {
        sender->_xOffset = newOffset;
        sender->_value = ((sender->maxValue() - sender->minValue())/218)*sender->_xOffset;
    }
}

void Slider::_onLeftButtonDown(Event::Mouse* event)
{
    auto sender = dynamic_cast<Slider*>(event->emitter());
    if (!sender->_downSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_downSound);
    }
}

void Slider::_onLeftButtonUp(Event::Mouse* event)
{
    auto sender = dynamic_cast<Slider*>(event->emitter());
    if (!sender->_upSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_upSound);
    }
}

Texture* Slider::texture() const
{
    if (_drag) return _imageList.images()->at(0)->texture();
    return _imageList.images()->at(1)->texture();
}

double Slider::minValue() const
{
    return _minValue;
}

void Slider::setMinValue(double value)
{
    _minValue = value;
}

double Slider::maxValue() const
{
    return _maxValue;
}

void Slider::setMaxValue(double value)
{
    _maxValue = value;
}

double Slider::value() const
{
    return _value;
}

void Slider::setValue(double value)
{
    _value = value;
    _xOffset = (218/(maxValue() - minValue())) * _value;
}

int Slider::x() const
{
    return _x + _xOffset;
}

}
}
