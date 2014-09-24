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
protected:
    int _x = 0;
    int _y = 0;
    int _xOffset = 0;
    int _yOffset = 0;
    std::shared_ptr<Texture> _texture;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
    bool _drag = false;
    bool _hovered = false;
    bool _visible = true;
public:
    UI(int x = 0, int y = 0);
    virtual ~UI();

    virtual int x();
    virtual void setX(int value);

    virtual int xOffset();
    virtual void setXOffset(int xOffset);

    virtual int y();
    virtual void setY(int value);

    virtual int yOffset();
    virtual void setYOffset(int yOffset);

    virtual std::shared_ptr<Texture> texture();
    virtual void setTexture(std::shared_ptr<Texture> texture);

    virtual void setVisible(bool value);
    virtual bool visible();

    virtual void think();
    virtual void render();

    virtual unsigned int width();
    virtual unsigned int height();
};

}
#endif // FALLTERGEIST_UI_H
