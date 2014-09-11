#ifndef FALLTERGEIST_EVENTEMITTER_H
#define FALLTERGEIST_EVENTEMITTER_H

// C++ standard includes
#include <map>
#include <vector>
#include <string>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Event;
class EventReciever;
class EventHandler;

typedef void (EventReciever::*EventRecieverMethod)(std::shared_ptr<Event>);

class EventEmitter
{
protected:
    std::map<std::string, std::vector<EventHandler*>> _eventHandlers;
public:
    EventEmitter();
    virtual ~EventEmitter();

    void addEventHandler(std::string eventName, EventReciever* reciever, EventRecieverMethod handler);
    void emitEvent(std::shared_ptr<Event> event);
    void removeEventHandlers(std::string eventName);
};

}
#endif // FALLTERGEIST_EVENTEMITTER_H
