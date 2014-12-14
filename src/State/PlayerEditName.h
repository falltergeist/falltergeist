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

#ifndef FALLTERGEIST_PlayerEditName_H
#define FALLTERGEIST_PlayerEditName_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
class TextArea;
class Image;

namespace State
{

class PlayerEditName : public State
{
protected:
    unsigned int _timer;
    TextArea* _name = 0;
    Image* _cursor = 0;
    std::map<char,char> _keyCodes;
public:
    PlayerEditName();
    ~PlayerEditName();
    void init();
    void think();
    void onDoneButtonClick(MouseEvent* event);
    void onKeyboardPress(KeyboardEvent* event);
};


}
}

#endif // FALLTERGEIST_PlayerEditName_H
