#include "../Game/AbstractTimer.h"
#include "../Event/Event.h"

namespace Falltergeist
{
    namespace Game
    {
        AbstractTimer::AbstractTimer(float interval) : _interval(interval)
        {
        }

        Event::Handler& AbstractTimer::tickHandler()
        {
            return _tickHandler;
        }

        void AbstractTimer::think(const float &deltaTime)
        {
            if (!_enabled) {
                return;
            }

            _timeTracked += deltaTime;

            if (_timeTracked >= _interval) {
                _timeTracked = _interval;
                // Invoke directly without Event Dispatcher, for now.
                Event::Event event("tick");
                if (!_repeat) {
                    _enabled = false;
                }
                _tickHandler.invoke(&event);
                _timeTracked = 0;
            }
        }

        void AbstractTimer::start()
        {
            _enabled = true;
            _timeTracked = 0;
        }

        void AbstractTimer::start(float interval, bool repeat)
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

        void AbstractTimer::setInterval(float interval)
        {
            _interval = interval;
        }
    }
}
