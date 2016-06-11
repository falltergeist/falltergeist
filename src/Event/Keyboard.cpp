/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../Event/Keyboard.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        Keyboard::Keyboard(Keyboard::Type type) : Event(typeToString(type))
        {
            _type = type;
        }

        Keyboard::Keyboard(const Keyboard& event, const std::string& newName) : Event(newName)
        {
            _keyCode = event._keyCode;
            _shiftPressed = event._shiftPressed;
            _controlPressed = event._controlPressed;
            _altPressed = event._altPressed;
        }

        Keyboard::Keyboard(const Keyboard& event) : Keyboard(event, event._name)
        {
        }

        Keyboard::~Keyboard()
        {
        }

        const char* Keyboard::typeToString(Keyboard::Type type)
        {
            switch (type)
            {
                case Type::KEY_DOWN: return "keydown";
                case Type::KEY_UP:   return "keyup";
                default: return "keyboard";
            }
        }

        Keyboard::Type Keyboard::originalType() const
        {
            return _type;
        }

        int Keyboard::keyCode() const
        {
            return _keyCode;
        }

        void Keyboard::setKeyCode(int value)
        {
            _keyCode = value;
        }

        bool Keyboard::shiftPressed() const
        {
            return _shiftPressed;
        }

        void  Keyboard::setShiftPressed(bool value)
        {
            _shiftPressed = value;
        }

        bool Keyboard::controlPressed() const
        {
            return _controlPressed;
        }

        void Keyboard::setControlPressed(bool value)
        {
            _controlPressed = value;
        }

        void Keyboard::setAltPressed(bool value)
        {
            this->_altPressed = value;
        }

        bool Keyboard::altPressed() const
        {
            return _altPressed;
        }
    }
}
