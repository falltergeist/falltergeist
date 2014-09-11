#ifndef FALLTERGEIST_EVENTRECIEVER_H
#define FALLTERGEIST_EVENTRECIEVER_H

// C++ standard includes
#include <memory>

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
    virtual void handle(std::shared_ptr<Event> event);
};

}
#endif // FALLTERGEIST_EVENTRECIEVER_H
