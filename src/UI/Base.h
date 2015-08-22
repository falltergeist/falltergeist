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

#ifndef FALLTERGEIST_UI_BASE_H
#define FALLTERGEIST_UI_BASE_H

// C++ standard includes

// Falltergeist includes
#include "../Event/Emitter.h"
#include "../Point.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{
    class Texture;
}

namespace UI
{

class Base : public Event::Emitter
{
public:
    Base(int x = 0, int y = 0);
    Base(const Point& pos);
    ~Base();

    // @todo: remove getters/setters for x, y, xOffset, yOffset, width, height?
    virtual int x() const;
    virtual void setX(int value);

    virtual int xOffset() const;
    virtual void setXOffset(int xOffset);

    virtual int y() const;
    virtual void setY(int value);

    virtual int yOffset() const;
    virtual void setYOffset(int yOffset);

    virtual Point position() const;
    virtual void setPosition(const Point& pos);

    virtual Point offset() const;
    virtual void setOffset(const Point& pos);

    virtual Graphics::Texture* texture() const;
    virtual void setTexture(Graphics::Texture* texture);

    virtual bool visible() const;
    virtual void setVisible(bool value);

    virtual void think();
    virtual void render(bool eggTransparency = false);
    virtual void handle(Event::Event* event);

    virtual Size size() const;
    virtual unsigned int width() const;
    virtual unsigned int height() const;

    virtual unsigned int pixel(const Point& pos);
    virtual unsigned int pixel(unsigned int x, int unsigned y);

protected:
    Point _position;
    Point _offset;

    Graphics::Texture* _texture = 0;
    Graphics::Texture* _tmptex = 0;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
    bool _drag = false;
    bool _hovered = false;
    bool _visible = true;
    // @todo Should it really be here?
    std::string _downSound = "";
    std::string _upSound = "";
};

}
}
#endif // FALLTERGEIST_UI_BASE_H
