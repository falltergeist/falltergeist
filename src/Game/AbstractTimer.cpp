#include "../Game/AbstractTimer.h"
#include "../Event/Event.h"

namespace Falltergeist
{
    namespace Game
    {
        AbstractTimer::AbstractTimer(unsigned interval) : _interval(interval)
        {
        }

        Event::Handler& AbstractTimer::tickHandler()
        {
            return _tickHandler;
        }

        void AbstractTimer::think(float deltaTime)
        {
            // TODO use nanoseconds
            if (_enabled && _getTime() > _lastTick + _interval) {
                // Invoke directly without Event Dispatcher, for now.
                Event::Event event("tick");
                if (!_repeat) {
                    _enabled = false;
                }
                _tickHandler.invoke(&event);
            }
        }

        void AbstractTimer::start()
        {
            _enabled = true;
            _lastTick = _getTime();
        }

        void AbstractTimer::start(unsigned int interval, bool repeat)
        {
            _interval = interval;
            _repeat = repeat;
            start();
        }

        void AbstractTimer::stop()
        {
            _enabled = false;
        }

        bool AbstractTimer::enabled() const
        {
            return _enabled;
        }

        unsigned int AbstractTimer::interval() const
        {
            return _interval;
        }

        void AbstractTimer::setInterval(unsigned int interval)
        {
            _interval = interval;
        }

        bool AbstractTimer::repeat() const
        {
            return _repeat;
        }

        void AbstractTimer::setRepeat(bool repeat)
        {
            _repeat = repeat;
        }
    }
}
