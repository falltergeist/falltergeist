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
#include "../UI/Base.h"

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Game/Game.h"
#include "../Game/DudeObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../LocationCamera.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

// Third party includes

namespace Falltergeist
{
using Base::make_unique;

namespace UI
{

Base::Base(int x, int y) : Event::Emitter()
{
    _x = x;
    _y = y;
}

Base::~Base()
{
    // Delete texture only if it wasn't allocated by Resource Manager
    if (_texture)
    {
        bool found = false;
        for (auto it = ResourceManager::getInstance()->textures()->begin(); it != ResourceManager::getInstance()->textures()->end(); ++it)
        {
            if (it->second == _texture)
            {
                found = true;
                break;
            }
        }
        if (!found) delete _texture;
    }
}

int Base::x() const
{
    return _x + _xOffset;
}

void Base::setX(int value)
{
    _x = value;
}

int Base::y() const
{
    return _y + _yOffset;
}

void Base::setY(int value)
{
    _y = value;
}

Graphics::Texture* Base::texture() const
{
    return _texture;
}

void Base::setTexture(Graphics::Texture* texture)
{
    _texture = texture;
}

void Base::think()
{
}

void Base::render(bool eggTransparency)
{

    if (eggTransparency)
    {
        auto dude = Game::getInstance()->player();

        if (!dude || !Game::getInstance()->locationState())
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();

        int egg_x = dude->hexagon()->x() - camera->x() - 63 + dude->ui()->xOffset();
        int egg_y = dude->hexagon()->y() - camera->y() - 78 + dude->ui()->yOffset();

        int egg_dx = x() - egg_x;
        int egg_dy = y() - egg_y;

        auto egg = ResourceManager::getInstance()->texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { egg_x, egg_y, (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { x(), y(), (int)texture()->width(), (int)texture()->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
            return;
        }

        if (!_tmptex) _tmptex = new Graphics::Texture(texture()->width(),texture()->height());
        texture()->copyTo(_tmptex);

        _tmptex->blitWithAlpha(egg, egg_dx, egg_dy);
        Game::getInstance()->renderer()->drawTexture(_tmptex, x(), y());
    }
    else
    {
        Game::getInstance()->renderer()->drawTexture(texture(), x(), y());
    }



}

void Base::setVisible(bool value)
{
    _visible = value;
}

bool Base::visible() const
{
    return _visible;
}

int Base::xOffset() const
{
    return _xOffset;
}

void Base::setXOffset(int xOffset)
{
    _xOffset = xOffset;
}

int Base::yOffset() const
{
    return _yOffset;
}

void Base::setYOffset(int yOffset)
{
    _yOffset = yOffset;
}

unsigned int Base::width() const
{
    if (!texture()) return 0;
    return texture()->width();
}

unsigned int Base::height() const
{
    if (!texture()) return 0;
    return texture()->height();
}

unsigned int Base::pixel(unsigned int x, unsigned int y)
{
    return texture() ? texture()->pixel(x, y) : 0;
}

void Base::handle(Event::Event* event)
{
    if (event->handled()) return;
    if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
    {
        int x = mouseEvent->x() - this->x();
        int y = mouseEvent->y() - this->y();

        //auto newEvent = make_unique<Event::Mouse>(mouseEvent);
        //std::unique_ptr<Event::Event> newEvent(new Event::Mouse(mouseEvent));

        if (this->pixel(x, y))
        {
            if (mouseEvent->name() == "mousemove")
            {
                if (_leftButtonPressed)
                {
                    //newEvent->setName( _drag ? "mousedrag" : "mousedragstart");
                    if (!_drag) _drag = true;
                    //emitEvent(std::unique_ptr<Event::Event>(new Event::Mouse(mouseEvent, _drag ? "mousedrag" : "mousedragstart")));
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, _drag ? "mousedrag" : "mousedragstart"));
                }
                if (!_hovered)
                {
                    _hovered = true;
                    //newEvent->setName("mousein");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mousein"));
                }
                else
                {
                    //newEvent->setName("mousemove");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mousemove"));
                }
            }
            else if (mouseEvent->name() == "mousedown")
            {
                if (mouseEvent->leftButton())
                {
                    _leftButtonPressed = true;
                    //emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouseleftdown"));
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouseleftdown"));
                }
                else if (mouseEvent->rightButton())
                {
                    _rightButtonPressed = true;
                    //newEvent->setName("mouserightdown");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouserightdown"));
                }
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                {
                    //newEvent->setName("mouseleftup");
                    //emitEvent(std::move(newEvent));
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouseleftup"));
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            //newEvent->setName("mousedragstop");
                            emitEvent(make_unique<Event::Mouse>(mouseEvent, "mousedragstop"));
                        }
                        //newEvent->setName("mouseleftclick");
                        emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouseleftclick"));
                    }
                    _leftButtonPressed = false;
                }
                else if (mouseEvent->rightButton())
                {
                    //newEvent->setName("mouserightup");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouserightup"));
                    if (_rightButtonPressed)
                    {
                        //newEvent->setName("mouserightclick");
                        emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouserightclick"));
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
                    //newEvent->setName("mousedrag");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mousedrag"));
                }
                if (_hovered)
                {
                    _hovered = false;
                    //newEvent->setName("mouseout");
                    emitEvent(make_unique<Event::Mouse>(mouseEvent, "mouseout"));
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
                            //newEvent->setName("mousedragstop");
                            emitEvent(make_unique<Event::Mouse>(mouseEvent, "mousedragstop"));
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

        /*
        if (newEvent->handled())
        {
            event->setHandled(true);
        }
        //*/
        return;
    }

    if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
    {
        //emitEvent(keyboardEvent);
        emitEvent(make_unique<Event::Keyboard>(*keyboardEvent));
    }
}

}
}
