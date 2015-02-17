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

// C++ standard includes

// Falltergeist includes
#include "../Graphics/ActiveUI.h"
#include "../Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

ActiveUI::ActiveUI(int x, int y) : EventEmitter(), UI(x, y)
{
}

ActiveUI::~ActiveUI()
{
}

void ActiveUI::handle(Event* event)
{
    if(auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {

        int x = mouseEvent->x() - this->x();
        int y = mouseEvent->y() - this->y();

        auto newEvent = new MouseEvent(mouseEvent);

        if (this->pixel(x, y))
        {
            if (mouseEvent->name() == "mousemove")
            {
                    if (_leftButtonPressed)
                    {
                        newEvent->setName( _drag ? "mousedrag" : "mousedragstart");
                        if (!_drag) _drag = true;
                        emitEvent(newEvent);
                    }
                    if (!_hovered)
                    {
                        _hovered = true;
                        newEvent->setName("mousein");
                        emitEvent(newEvent);
                    }
                    else
                    {
                        newEvent->setName("mousemove");
                        emitEvent(newEvent);
                    }
            }
            else if (mouseEvent->name() == "mousedown")
            {
                    if (mouseEvent->leftButton())
                    {
                        _leftButtonPressed = true;
                        newEvent->setName("mouseleftdown");
                        emitEvent(newEvent);
                    }
                    else if (mouseEvent->rightButton())
                    {
                        _rightButtonPressed = true;
                        newEvent->setName("mouserightdown");
                        emitEvent(newEvent);
                    }
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                    {
                        newEvent->setName("mouseleftup");
                        emitEvent(newEvent);
                        if (_leftButtonPressed)
                        {
                            if (_drag)
                            {
                                _drag = false;
                                newEvent->setName("mousedragstop");
                                emitEvent(newEvent);
                            }
                            newEvent->setName("mouseleftclick");
                            emitEvent(newEvent);
                        }
                        _leftButtonPressed = false;
                    }
                    else if(mouseEvent->rightButton())
                    {
                        newEvent->setName("mouserightup");
                        emitEvent(newEvent);
                        if (_rightButtonPressed)
                        {
                            newEvent->setName("mouserightclick");
                            emitEvent(newEvent);
                        }
                        _rightButtonPressed = false;
                    }
            }
        }
        else
        {
            if (mouseEvent->name() == "mousemove" && _hovered)
            {
                if (_drag)
                {
                    newEvent->setName("mousedrag");
                    emitEvent(newEvent);
                }
                _hovered = false;
                newEvent->setName("mouseout");
                emitEvent(newEvent);
            }
            else if (mouseEvent->name() == "mousemove" && !_hovered)
            {
                if (_drag)
                {
                    newEvent->setName("mousedrag");
                    emitEvent(newEvent);
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
                            newEvent->setName("mousedragstop");
                            emitEvent(newEvent);
                        }
                        newEvent->setName("mouseleftup");
                        emitEvent(newEvent);
                        _leftButtonPressed = false;
                    }
                }
                else if(mouseEvent->rightButton())
                {
                    if (_rightButtonPressed)
                    {
                        newEvent->setName("mouserightup");
                        emitEvent(newEvent);
                        _rightButtonPressed = false;
                    }
                }
            }
        }
        event->setHandled(newEvent->handled());
        delete newEvent;
        return;
    }

    if(auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        emitEvent(keyboardEvent);
    }

}

}
