#include "../Event/EventEmitter.h"
#include "../Event/EventHandler.h"
#include "../Event/Event.h"

namespace Falltergeist
{

EventEmitter::EventEmitter()
{
}

EventEmitter::~EventEmitter()
{
}

void EventEmitter::addEventHandler(std::string eventName, EventReciever* reciever, EventRecieverMethod handler)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end())
    {
        _eventHandlers.insert(std::make_pair(eventName, new std::vector<EventHandler*>()));
    }

    _eventHandlers.at(eventName)->push_back(new EventHandler(reciever, handler));
}

void EventEmitter::emitEvent(Event* event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;

    event->setEmitter(this);
    for (EventHandler* eventHandler : *_eventHandlers.at(event->name()))
    {
        eventHandler->operator()(event);
    }
}

void EventEmitter::removeEventHandlers(std::string eventName)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end()) return;

    delete _eventHandlers.at(eventName);
    _eventHandlers.erase(eventName);
}

}
