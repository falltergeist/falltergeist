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
#include "../Engine/ActiveUI.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

ActiveUI::ActiveUI(int x, int y) : EventEmitter(), EventReciever(), UI(x, y)
{
}

void ActiveUI::handle(Event* event)
{
    if(auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        if (!texture()) return;

        int x = mouseEvent->x() - this->x();
        int y = mouseEvent->y() - this->y();

        auto event = new MouseEvent(mouseEvent);
        event->setEmitter(this);

        unsigned int alpha = texture()->pixel(x, y) & 0xFF;
        if (alpha > 0)
        {
            if (mouseEvent->name() == "mousemove")
            {
                    if (_leftButtonPressed)
                    {
                        event->setName( _drag ? "mousedrag" : "mousedragstart");
                        if (!_drag) _drag = true;
                        emitEvent(event);
                    }
                    if (!_hovered)
                    {
                        _hovered = true;
                        event->setName("mousein");
                        emitEvent(event);
                    }
                    else
                    {
                        event->setName("mousemove");
                        emitEvent(event);
                    }
            }
            else if (mouseEvent->name() == "mousedown")
            {
                    if (mouseEvent->leftButton())
                    {
                        _leftButtonPressed = true;
                        event->setName("mouseleftdown");
                        emitEvent(event);
                    }
                    else if (mouseEvent->rightButton())
                    {
                        _rightButtonPressed = true;
                        event->setName("mouserightdown");
                        emitEvent(event);
                    }
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                    {
                        event->setName("mouseleftup");
                        emitEvent(event);
                        if (_leftButtonPressed)
                        {
                            if (_drag)
                            {
                                _drag = false;
                                event->setName("mousedragstop");
                                emitEvent(event);
                            }
                            event->setName("mouseleftclick");
                            emitEvent(event);
                        }
                        _leftButtonPressed = false;
                    }
                    else if(mouseEvent->rightButton())
                    {
                        event->setName("mouserightup");
                        emitEvent(event);
                        if (_rightButtonPressed)
                        {
                            event->setName("mouserightclick");
                            emitEvent(event);
                        }
                        _rightButtonPressed = false;
                    }
             }
        }
        else
        {
            if (mouseEvent->name() == "mousemove"&& _hovered)
            {
                if (_drag)
                {
                    event->setName("mousedrag");
                    emitEvent(event);
                }
                _hovered = false;
                event->setName("mouseout");
                emitEvent(event);
            }
            else if (mouseEvent->name() == "mousemove" && !_hovered)
            {
                if (_drag)
                {
                    event->setName("mousedrag");
                    emitEvent(event);
                }
            }
            else if(mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                {
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            event->setName("mousedragstop");
                            emitEvent(event);
                        }
                        event->setName("mouseleftup");
                        emitEvent(event);
                        _leftButtonPressed = false;
                    }
                }
                else if(mouseEvent->rightButton())
                {
                    if (_rightButtonPressed)
                    {
                        event->setName("mouserightup");
                        emitEvent(event);
                        _rightButtonPressed = false;
                    }
                }
            }
        }
        return;
    }

    if(auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        emitEvent(keyboardEvent);
    }

}

}
