/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <memory>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Game/Game.h"
#include "../Graphics/Point.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{


Slider::Slider(const Point& pos) : Base(pos)
{
}

Slider::Slider(int x, int y) : Falltergeist::UI::Base(Point(x, y))
{
    mouseDragHandler().add(std::bind(&Slider::_onDrag, this, std::placeholders::_1));
    mouseDownHandler().add(std::bind(&Slider::_onLeftButtonDown, this, std::placeholders::_1));
    mouseUpHandler().add(std::bind(&Slider::_onLeftButtonUp, this, std::placeholders::_1));
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
        //if (!texture()) return;

        Point ofs = mouseEvent->position() - _position;

        bool opaque = _imageList.images().at(0)->opaque(mouseEvent->position() - _offset);

        //if we are in slider coordinates and not on thumb (slider size = 218 + thumb size, thumb size = 21)
        if (ofs.x() > 0 && ofs.x() < 239 && ofs.y() > 0 && ofs.y() < _imageList.images().at(0)->size().height() && !opaque)
        {
            //on left button up only when not dragging thumb
            if (mouseEvent->name() == "mouseup" && mouseEvent->leftButton() && !_drag)
            {
                ofs -= Point(10, 0); //~middle of thumb
                if (ofs.x() < 0)
                {
                    ofs.setX(0);
                }
                else if (ofs.y() > 218)
                {
                    ofs.setX(218);
                }
                _offset.setX(ofs.x());
                _value = ((maxValue() - minValue()) / 218.f) * (float)_offset.x();
                emitEvent(std::make_unique<Event::Event>("change"), changeHandler());
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
    auto sender = dynamic_cast<Slider*>(event->target());
    auto newOffset = sender->_offset.x() + event->offset().x();
    if (newOffset <= 218 && newOffset >= 0)
    {
        sender->_offset.setX(newOffset);
        sender->_value = ((sender->maxValue() - sender->minValue())/218.f)*(float)sender->offset().x();
        emitEvent(std::make_unique<Event::Event>("change"), changeHandler());
    }
}

void Slider::_onLeftButtonDown(Event::Mouse* event)
{
    auto sender = dynamic_cast<Slider*>(event->target());
    if (!sender->_downSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_downSound);
    }
}

void Slider::_onLeftButtonUp(Event::Mouse* event)
{
    auto sender = dynamic_cast<Slider*>(event->target());
    if (!sender->_upSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_upSound);
    }
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
    _offset.setX((218.f/(maxValue() - minValue())) * _value);
    emitEvent(std::make_unique<Event::Event>("change"), changeHandler());
}

Event::Handler& Slider::changeHandler()
{
    return _changeHandler;
}

void Slider::render(bool eggTransparency)
{

    _imageList.images().at(0)->setPosition(position());
    _imageList.images().at(1)->setPosition(position());
    if (_drag) _imageList.images().at(0)->render(eggTransparency);
    else _imageList.images().at(1)->render(eggTransparency);
}

bool Slider::opaque(const Point &pos)
{
    return _imageList.images().at(0)->opaque(pos);
}

Size Slider::size() const
{
    return _imageList.images().at(0)->size();
}
}
}
