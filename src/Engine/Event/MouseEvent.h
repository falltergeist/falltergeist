#ifndef FALLTERGEIST_MOUSEEVENT_H
#define FALLTERGEIST_MOUSEEVENT_H

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

class MouseEvent : public Event
{
protected:
    int _x = 0;
    int _y = 0;
    int _xOffset = 0;
    int _yOffset = 0;
    int _leftButton = false;
    int _rightButton = false;
public:
    MouseEvent(std::string eventName = "mouse");
    MouseEvent(const MouseEvent* event);
    virtual ~MouseEvent();

    void setX(int value);
    int x();

    void setY(int value);
    int y();

    void setXOffset(int value);
    int xOffset();

    void setYOffset(int value);
    int yOffset();

    bool leftButton();
    void setLeftButton(bool value);

    bool rightButton();
    void setRightButton(bool value);
};

}
#endif // FALLTERGEIST_MOUSEEVENT_H
