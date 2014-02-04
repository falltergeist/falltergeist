#ifndef FALLTERGEIST_EVENTRECIEVER_H
#define FALLTERGEIST_EVENTRECIEVER_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Event;

class EventReciever
{
public:
    EventReciever();
    virtual ~EventReciever();
    virtual void handle(Event* event);
};

}
#endif // FALLTERGEIST_EVENTRECIEVER_H
