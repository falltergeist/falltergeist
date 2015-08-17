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

#ifndef FALLTERGEIST_UI_H
#define FALLTERGEIST_UI_H

// C++ standard includes
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Texture;

class UI
{
public:
    UI(int x = 0, int y = 0);
    virtual ~UI();

    virtual int x() const;
    virtual void setX(int value);

    virtual int xOffset();
    virtual void setXOffset(int xOffset);

    virtual int y() const;
    virtual void setY(int value);

    virtual int yOffset();
    virtual void setYOffset(int yOffset);

    virtual Texture* texture() const;
    virtual void setTexture(Texture* texture);

    virtual void setVisible(bool value);
    virtual bool visible();

    virtual void think();
    virtual void render(bool eggTransparency = false);

    virtual unsigned int width() const;
    virtual unsigned int height() const;

    virtual unsigned int pixel(unsigned int x, int unsigned y);

protected:
    int _x = 0;
    int _y = 0;
    int _xOffset = 0;
    int _yOffset = 0;
    Texture* _texture = 0;
    Texture* _tmptex = 0;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
    bool _drag = false;
    bool _hovered = false;
    bool _visible = true;
};

}
#endif // FALLTERGEIST_UI_H
