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
        std::vector<EventHandler*> vector;
        _eventHandlers.insert(std::make_pair(eventName, vector));
    }

    _eventHandlers.at(eventName).push_back(new EventHandler(reciever, handler));
}

void EventEmitter::emitEvent(std::shared_ptr<Event> event)
{
    if (_eventHandlers.find(event->name()) == _eventHandlers.end()) return;

    event->setEmitter(this);
    for (auto eventHandler : _eventHandlers.at(event->name()))
    {
        auto e = event;
        e->setReciever(eventHandler->reciever());
        eventHandler->operator()(e);
    }
}

void EventEmitter::removeEventHandlers(std::string eventName)
{
    if (_eventHandlers.find(eventName) == _eventHandlers.end()) return;

    while (!_eventHandlers.at(eventName).empty())
    {
        delete _eventHandlers.at(eventName).back();
        _eventHandlers.at(eventName).pop_back();
    }
    _eventHandlers.erase(eventName);
}

}
