#ifndef FALLTERGEIST_KEYBOARDEVENT_H
#define FALLTERGEIST_KEYBOARDEVENT_H

// C++ standard includes

// Falltergeist includes
#include "../Event/Event.h"

// Third party includes

namespace Falltergeist
{

class KeyboardEvent : public Event
{
protected:
    int _keyCode = 0;
    bool _shiftPressed = false;
public:
    KeyboardEvent(std::string name = "keyboard");
    virtual ~KeyboardEvent();
    int keyCode();
    void setKeyCode(int value);
    bool shiftPressed();
    void setShiftPressed(bool value);
};

}
#endif // FALLTERGEIST_KEYBOARDEVENT_H
