#include "../Event/Event.h"
#include "../Game/Timer.h"

namespace Falltergeist
{
    namespace Game
    {
        Timer::Timer(const float &interval) : _interval(interval)
        {
        }

        Event::Handler& Timer::tickHandler()
        {
            return _tickHandler;
        }

        void Timer::think(const float &deltaTime, const uint32_t ticks)
        {
            if (!_enabled || ticks == _lastTick) {
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

        void Timer::start(const uint32_t ticks)
        {
            _enabled = true;
            _timeTracked = 0;
            _lastTick = ticks;
        }

        void Timer::start(const uint32_t ticks, const float &interval, bool repeat)
        {
            _interval = interval;
            _repeat = repeat;
            start(ticks);
        }

        void Timer::stop()
        {
            _enabled = false;
        }

        bool Timer::enabled() const
        {
            return _enabled;
        }

        void Timer::setInterval(const float &interval)
        {
            _interval = interval;
        }
    }
}
