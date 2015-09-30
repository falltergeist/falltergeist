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
namespace UI
{

using namespace Base;

Base::Base(int x, int y) : Base(Point(x, y))
{
}

Base::Base(const Point& pos) : Event::Emitter()
{
    _position = pos;
}

Base::~Base()
{
}

int Base::x() const
{
    return (position() + offset()).x();
}

void Base::setX(int value)
{
    setPosition(Point(value, position().y()));
}

int Base::y() const
{
    return _position.y() + _offset.y();
}

void Base::setY(int value)
{
    setPosition(Point(position().x(), value));
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
            Game::getInstance()->renderer()->drawTexture(texture(), position());
            return;
        }

        auto camera = Game::getInstance()->locationState()->camera();

        Point eggPos = dude->hexagon()->position() - camera->topLeft() - Point(63, 78) + dude->ui()->offset();

        Point eggDelta = position() - eggPos;

        auto egg = ResourceManager::getInstance()->texture("data/egg.png");

        //check if egg and texture intersects
        SDL_Rect egg_rect = { eggPos.x(), eggPos.y(), (int)egg->width(), (int)egg->height() };
        SDL_Rect tex_rect = { x(), y(), (int)texture()->width(), (int)texture()->height() };

        if (!SDL_HasIntersection(&egg_rect, &tex_rect))
        {
            Game::getInstance()->renderer()->drawTexture(texture(), position());
            return;
        }

        if (!_tmptex)
        {
            _tmptex = make_unique<Graphics::Texture>(texture()->width(), texture()->height());
        }
        texture()->copyTo(_tmptex.get());

        _tmptex->blitWithAlpha(egg, eggDelta.x(), eggDelta.y());
        Game::getInstance()->renderer()->drawTexture(_tmptex.get(), position());
    }
    else
    {
        Game::getInstance()->renderer()->drawTexture(texture(), position());
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

Point Base::position() const
{
    return _position + _offset;
}

void Base::setPosition(const Point& pos)
{
    _position = pos;
}

Point Base::offset() const
{
    return _offset;
}

void Base::setOffset(const Point& pos)
{
    _offset = pos;
}

void Base::setOffset(int x, int y)
{
    setOffset(Point(x, y));
}

Size Base::size() const
{
    auto tex = texture();
    if (!tex) return Size(0, 0);
    return Size(tex->width(), tex->height());
}

unsigned int Base::pixel(const Point& pos)
{
    return texture() ? texture()->pixel(pos.x(), pos.y()) : 0;
}

unsigned int Base::pixel(unsigned int x, unsigned int y)
{
    return pixel(Point(x, y));
}

void Base::handle(Event::Event* event)
{
    if (event->handled()) return;
    if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
    {
        Point pos = mouseEvent->position() - this->position();

        auto newEvent = new Event::Mouse(*mouseEvent);

        if (this->pixel(pos))
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
                else if (mouseEvent->rightButton())
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
            if (mouseEvent->name() == "mousemove")
            {
                if (_drag)
                {
                    newEvent->setName("mousedrag");
                    emitEvent(newEvent);
                }
                if (_hovered)
                {
                    _hovered = false;
                    newEvent->setName("mouseout");
                    emitEvent(newEvent);
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
                            emitEvent(newEvent);
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

    if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
    {
        emitEvent(keyboardEvent);
    }
}

void Base::_generateTexture(unsigned int width, unsigned int height)
{
    auto ptr = new Graphics::Texture(width, height);
    _generatedTexture.reset(ptr);
    setTexture(ptr);
}

unsigned Base::width() const
{
    return size().width();
}

unsigned Base::height() const
{
    return size().height();
}

}
}
