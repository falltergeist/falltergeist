// Project includes
#include "../Event/Event.h"
#include "../Game/Timer.h"

// Third-party includes

// stdlib

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

        void Timer::think(const float &deltaTime)
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

        void Timer::start()
        {
            _enabled = true;
            _timeTracked = 0;
        }

        void Timer::start(const float &interval, bool repeat)
        {
            _interval = interval;
            _repeat = repeat;
            start();
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
