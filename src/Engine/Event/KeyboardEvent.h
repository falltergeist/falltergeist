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
public:
    KeyboardEvent(std::string name = "keyboard");
    virtual ~KeyboardEvent();
};

}
#endif // FALLTERGEIST_KEYBOARDEVENT_H
