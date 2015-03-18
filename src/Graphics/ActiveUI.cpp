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
#include "../Event/EventSender.h"
#include "../Event/EventManager.h"
#include "../Graphics/ActiveUI.h"
#include "../Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

ActiveUI::ActiveUI(int x, int y) : UI(x, y), EventSender()
{
}

ActiveUI::~ActiveUI()
{
}

void ActiveUI::handle(Event* event)
{
    if (event->handled()) return;
    if (auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        int x = mouseEvent->x() - this->x();
        int y = mouseEvent->y() - this->y();

        auto newEvent = new MouseEvent(mouseEvent);
        newEvent->setSender(this);

        if (this->pixel(x, y))
        {
            if (mouseEvent->name() == "mousemove")
            {
                if (_leftButtonPressed)
                {
                    newEvent->setName( _drag ? "mousedrag" : "mousedragstart");
                    if (!_drag) _drag = true;
                    EventManager::getInstance()->handle(newEvent);
                }
                if (!_hovered)
                {
                    _hovered = true;
                    newEvent->setName("mousein");
                    EventManager::getInstance()->handle(newEvent);
                }
                else
                {
                    newEvent->setName("mousemove");
                    EventManager::getInstance()->handle(newEvent);
                }
            }
            else if (mouseEvent->name() == "mousedown")
            {
                if (mouseEvent->leftButton())
                {
                    _leftButtonPressed = true;
                    newEvent->setName("mouseleftdown");
                    EventManager::getInstance()->handle(newEvent);
                }
                else if (mouseEvent->rightButton())
                {
                    _rightButtonPressed = true;
                    newEvent->setName("mouserightdown");
                    EventManager::getInstance()->handle(newEvent);
                }
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                {
                    newEvent->setName("mouseleftup");
                    EventManager::getInstance()->handle(newEvent);
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            newEvent->setName("mousedragstop");
                            EventManager::getInstance()->handle(newEvent);
                        }
                        newEvent->setName("mouseleftclick");
                        EventManager::getInstance()->handle(newEvent);
                    }
                    _leftButtonPressed = false;
                }
                else if (mouseEvent->rightButton())
                {
                    newEvent->setName("mouserightup");
                    EventManager::getInstance()->handle(newEvent);
                    if (_rightButtonPressed)
                    {
                        newEvent->setName("mouserightclick");
                        EventManager::getInstance()->handle(newEvent);
                    }
                    _rightButtonPressed = false;
                }
            }
        }
        else
        {
            if (mouseEvent->name() == "mousemove")
            {
                if (_drag)
                {
                    newEvent->setName("mousedrag");
                    EventManager::getInstance()->handle(newEvent);
                }
                if (_hovered)
                {
                    _hovered = false;
                    newEvent->setName("mouseout");
                    EventManager::getInstance()->handle(newEvent);
                }
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                {
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            newEvent->setName("mousedragstop");
                            EventManager::getInstance()->handle(newEvent);
                        }
                        _leftButtonPressed = false;
                    }
                }
                else if (mouseEvent->rightButton())
                {
                    if (_rightButtonPressed)
                    {
                        _rightButtonPressed = false;
                    }
                }
            }
        }
        if (newEvent->handled())
        {
            event->setHandled(true);
        }
        delete newEvent;
        return;
    }

    if (auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        keyboardEvent->setSender(this);
        EventManager::getInstance()->handle(keyboardEvent);
    }
}

}
