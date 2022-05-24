// Project includes
#include "../Event/Keyboard.h"

// Third-party includes

// stdlib

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
