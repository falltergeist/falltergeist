#include "../Event/Event.h"
#include "../Game/Timer.h"
#include "../Game/Game.h"
#include "../Game/Time.h"
#include <SDL.h>

namespace Falltergeist
{
    namespace Game
    {
        TimerAbstract::TimerAbstract(unsigned interval) : _interval(interval)
        {
        }

        Event::Handler& TimerAbstract::tickHandler()
        {
            return _tickHandler;
        }

        void TimerAbstract::think()
        {
            if (_enabled && _getTime() > _lastTick + _interval) {
                // Invoke directly without Event Dispatcher, for now.
                Event::Event event("tick");
                if (!_repeat) {
                    _enabled = false;
                }
                _tickHandler.invoke(&event);
            }
        }

        void TimerAbstract::start()
        {
            _enabled = true;
            _lastTick = _getTime();
        }

        void TimerAbstract::start(unsigned int interval, bool repeat)
        {
            _interval = interval;
            _repeat = repeat;
            start();
        }

        void TimerAbstract::stop()
        {
            _enabled = false;
        }

        bool TimerAbstract::enabled() const
        {
            return _enabled;
        }

        unsigned int TimerAbstract::interval() const
        {
            return _interval;
        }

        void TimerAbstract::setInterval(unsigned int interval)
        {
            _interval = interval;
        }

        bool TimerAbstract::repeat() const
        {
            return _repeat;
        }

        void TimerAbstract::setRepeat(bool repeat)
        {
            _repeat = repeat;
        }

        Timer::Timer(unsigned interval) : TimerAbstract(interval)
        {
        }

        unsigned int Timer::_getTime()
        {
            return SDL_GetTicks();
        }

        GameTimer::GameTimer(std::shared_ptr<Time> gameTime, unsigned interval) : TimerAbstract(interval)
        {
            _gameTime = gameTime;
        }

        unsigned int GameTimer::_getTime()
        {
            return _gameTime->ticks();
        }
    }
}
