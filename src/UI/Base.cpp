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

Base::Base(const Point& pos) : Event::EventTarget(Game::getInstance()->eventDispatcher())
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
    if (_tmptex)
    {
        return _tmptex->pixel((unsigned)pos.x(), (unsigned)pos.y()) & 0xFF; // return only alpha channel
    }
    auto tex = texture();
    return tex ? tex->pixel((unsigned)pos.x(), (unsigned)pos.y()) : 0;
}

unsigned int Base::pixel(unsigned int x, unsigned int y)
{
    return pixel(Point(x, y));
}

void Base::handle(Event::Event* event)
{
    if (event->handled()) return;
    // TODO: get rid of dynamic_casts by using template member function?
    if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
    {
        Point pos = mouseEvent->position() - this->position();

        if (!mouseEvent->obstacle() && this->pixel(pos)) // mouse cursor is over the element
        {
            if (mouseEvent->name() == "mousemove")
            {
                if (_leftButtonPressed)
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, _drag ? "mousedrag" : "mousedragstart"), _drag ? mouseDragHandler() : mouseDragStartHandler());
                    if (!_drag) _drag = true;
                }
                if (!_hovered)
                {
                    _hovered = true;
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mousein"), mouseInHandler());
                }
                else
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mousemove"), mouseMoveHandler());
                }
            }
            else if (mouseEvent->name() == "mousedown")
            {
                if (mouseEvent->leftButton())
                {
                    _leftButtonPressed = true;
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouseleftdown"), mouseDownHandler());
                }
                else if (mouseEvent->rightButton())
                {
                    _rightButtonPressed = true;
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouserightdown"), mouseDownHandler());
                }
                // mousedown event can not be "interesting" for any other UI's that "behind" this UI,
                // so we can safely stop event capturing now
                mouseEvent->setHandled(true);
            }
            else if (mouseEvent->name() == "mouseup")
            {
                if (mouseEvent->leftButton())
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouseleftup"), mouseUpHandler());
                    if (_leftButtonPressed)
                    {
                        if (_drag)
                        {
                            _drag = false;
                            emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mousedragstop"), mouseDragStopHandler());
                        }
                        emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouseleftclick"), mouseClickHandler());
                    }
                    _leftButtonPressed = false;
                }
                else if (mouseEvent->rightButton())
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouserightup"), mouseUpHandler());
                    if (_rightButtonPressed)
                    {
                        emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouserightclick"), mouseClickHandler());
                    }
                    _rightButtonPressed = false;
                }
            }
            mouseEvent->setObstacle(true);
        }
        else // mouse cursor is outside of this element or other element is in front
        {
            // stop processing if this element has no active interactions with the mouse
            if (!_hovered && !_leftButtonPressed && !_rightButtonPressed && !_drag)
            {
                return;
            }
            if (mouseEvent->name() == "mousemove")
            {
                if (_drag)
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mousedrag"), mouseDragHandler());
                }
                if (_hovered)
                {
                    _hovered = false;
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mouseout"), mouseOutHandler());
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
                            emitEvent(make_unique<Event::Mouse>(*mouseEvent, "mousedragstop"), mouseDragStopHandler());
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
        return;
    }

    if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
    {
        if (keyboardEvent->name() == "keyup")
        {
            emitEvent(make_unique<Event::Keyboard>(*keyboardEvent), keyUpHandler());
        }
        else if (keyboardEvent->name() == "keydown")
        {
            emitEvent(make_unique<Event::Keyboard>(*keyboardEvent), keyDownHandler());
        }
    }
}

void Base::_generateTexture(unsigned int width, unsigned int height)
{
    if (!_generatedTexture || _generatedTexture->width() != width || _generatedTexture->height() != height)
    {
        _generatedTexture = make_unique<Graphics::Texture>(width, height);
        setTexture(_generatedTexture.get());
    }
}

unsigned Base::width() const
{
    return size().width();
}

unsigned Base::height() const
{
    return size().height();
}


Event::KeyboardHandler& Base::keyDownHandler()
{
    return _keyDownHandler;
}

Event::KeyboardHandler& Base::keyUpHandler()
{
    return _keyUpHandler;
}

Event::MouseHandler& Base::mouseDragStartHandler()
{
    return _mouseDragStartHandler;
}

Event::MouseHandler& Base::mouseDragHandler()
{
    return _mouseDragHandler;
}

Event::MouseHandler& Base::mouseDragStopHandler()
{
    return _mouseDragStopHandler;
}

Event::MouseHandler& Base::mouseInHandler()
{
    return _mouseInHandler;
}

Event::MouseHandler& Base::mouseMoveHandler()
{
    return _mouseMoveHandler;
}

Event::MouseHandler& Base::mouseOutHandler()
{
    return _mouseOutHandler;
}

Event::MouseHandler& Base::mouseClickHandler()
{
    return _mouseClickHandler;
}

Event::MouseHandler& Base::mouseDownHandler()
{
    return _mouseDownHandler;
}

Event::MouseHandler& Base::mouseUpHandler()
{
    return _mouseUpHandler;
}

}
}
