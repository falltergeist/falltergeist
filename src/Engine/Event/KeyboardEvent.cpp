// C++ standard includes

// Falltergeist includes
#include "../Event/KeyboardEvent.h"

// Third party includes

namespace Falltergeist
{

KeyboardEvent::KeyboardEvent(std::string name) : Event(name)
{
}

KeyboardEvent::~KeyboardEvent()
{
}

int KeyboardEvent::keyCode()
{
    return _keyCode;
}

void KeyboardEvent::setKeyCode(int value)
{
    _keyCode = value;
}

bool KeyboardEvent::shiftPressed()
{
    return _shiftPressed;
}

void  KeyboardEvent::setShiftPressed(bool value)
{
    _shiftPressed = value;
}

}
