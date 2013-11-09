#include "../Event/MouseEvent.h"

namespace Falltergeist
{

MouseEvent::MouseEvent(std::string name) : Event(name)
{
}

MouseEvent::MouseEvent(const MouseEvent* event) : Event("mouse")
{
    _x = event->_x;
    _y = event->_y;
    _xOffset = event->_xOffset;
    _yOffset = event->_yOffset;
    _leftButton = event->_leftButton;
    _rightButton = event->_rightButton;
    _name = event->_name;
}

MouseEvent::~MouseEvent()
{
}

void MouseEvent::setX(int value)
{
    _x = value;
}

int MouseEvent::x()
{
    return _x;
}

void MouseEvent::setY(int value)
{
    _y = value;
}

int MouseEvent::y()
{
    return _y;
}

void MouseEvent::setXOffset(int value)
{
    _xOffset = value;
}

int MouseEvent::xOffset()
{
    return _xOffset;
}

void MouseEvent::setYOffset(int value)
{
    _yOffset = value;
}

int MouseEvent::yOffset()
{
    return _yOffset;
}

void MouseEvent::setLeftButton(bool value)
{
    _leftButton = value;
}

bool MouseEvent::leftButton()
{
    return _leftButton;
}

void MouseEvent::setRightButton(bool value)
{
    _rightButton = value;
}

bool MouseEvent::rightButton()
{
    return _rightButton;
}

}
