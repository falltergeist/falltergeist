// Project includes
#include "../Event/Mouse.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Event
    {
        Mouse::Mouse(Type type) : Event(typeToString(type))
        {
            _type = type;
        }

        Mouse::Mouse(const Mouse& event, const std::string& newName) : Event(newName)
        {
            _button = event._button;
            _position = event._position;
            _shiftPressed = event._shiftPressed;
            _controlPressed = event._controlPressed;
            _altPressed = event._altPressed;
        }

        Mouse::Mouse(const Mouse& event) : Mouse(event, event._name)
        {
        }

        Mouse::~Mouse()
        {
        }

        const char* Mouse::typeToString(Mouse::Type type)
        {
            switch (type)
            {
                case Type::BUTTON_DOWN: return "mousedown";
                case Type::BUTTON_UP:   return "mouseup";
                case Type::MOVE:        return "mousemove";
                default: return "mouse";
            }
        }

        Mouse::Type Mouse::originalType() const
        {
            return _type;
        }

        bool Mouse::leftButton() const
        {
            return _button == Button::LEFT;
        }

        bool Mouse::rightButton() const
        {
            return _button == Button::RIGHT;
        }

        Mouse::Button Mouse::button() const
        {
            return _button;
        }

        void Mouse::setButton(Mouse::Button button)
        {
            _button = button;
        }

        void Mouse::setControlPressed(bool value)
        {
            this->_controlPressed = value;
        }

        bool Mouse::controlPressed() const
        {
            return _controlPressed;
        }

        void Mouse::setShiftPressed(bool value)
        {
            this->_shiftPressed = value;
        }

        bool Mouse::shiftPressed() const
        {
            return _shiftPressed;
        }

        const Graphics::Point& Mouse::position() const
        {
            return _position;
        }

        void Mouse::setPosition(const Graphics::Point& position)
        {
            _position = position;
        }

        bool Mouse::altPressed() const
        {
            return _altPressed;
        }

        void Mouse::setAltPressed(bool altPressed)
        {
            _altPressed = altPressed;
        }
    }
}
