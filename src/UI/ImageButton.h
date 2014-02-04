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

#ifndef FALLTERGEIST_IMAGEBUTTON_H
#define FALLTERGEIST_IMAGEBUTTON_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/Event/Event.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/UI.h"

// Third party includes

namespace Falltergeist
{

class ImageButton : public EventEmitter, public EventReciever, public UI
{
protected:
    unsigned int _state = 1;
    unsigned int _states = 2;
    bool _checkboxMode = false; // remember new state after click
    bool _pressed = false;

    std::vector<Texture*> _textures;
    void _onLeftButtonDown(MouseEvent* event);
    void _onLeftButtonUp(MouseEvent* event);
public:
    enum ButtonType {
        TYPE_SMALL_RED_CIRCLE = 1,
        TYPE_BIG_RED_CIRCLE,
        TYPE_SKILL_TOGGLE,
        TYPE_PLUS,
        TYPE_MINUS,
        TYPE_LEFT_ARROW,
        TYPE_RIGHT_ARROW,
        TYPE_CHECKBOX
    };
    ImageButton(unsigned int type, int x = 0, int y = 0);
    ~ImageButton();

    void setState(unsigned int value);
    virtual Texture* texture();
};

}
#endif // FALLTERGEIST_IMAGEBUTTON_H
