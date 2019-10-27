#include "../Game/CountdownTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        CountdownTimer::CountdownTimer(uint32_t seconds, uint32_t milliseconds, uint32_t microseconds, uint32_t nanoseconds)
        {
            _seconds = seconds;
            _milliseconds = milliseconds;
            _microseconds = microseconds;
            _nanoseconds = nanoseconds;
        }

        void CountdownTimer::think(uint32_t nanosecondsPassed)
        {
            if (isFinished()) {
                return;
            }

            uint32_t microseconds = nanosecondsPassed / 1000;
            uint32_t nanoseconds = nanosecondsPassed % 1000;

            if (_nanoseconds >= nanoseconds) {
                _nanoseconds -= nanoseconds;
            } else {
                if (_seconds > 0 || _milliseconds > 0 || _microseconds > 0) {
                    microseconds++;
                    _nanoseconds = 1000 + (_nanoseconds - nanoseconds);
                } else {
                    _nanoseconds = 0;
                }
            }

            if (microseconds > 0) {
                _decreaseMicroseconds(microseconds);
            }
        }

        bool CountdownTimer::isFinished()
        {
            return _seconds == 0 && _milliseconds == 0 && _microseconds == 0 && _nanoseconds == 0;
        }

        void CountdownTimer::_decreaseMicroseconds(uint32_t microseconds)
        {
            uint32_t milliseconds = microseconds / 1000;
            microseconds = microseconds % 1000;

            if (_microseconds >= microseconds) {
                _microseconds -= microseconds;
            } else {
                if (_seconds > 0 || _milliseconds > 0) {
                    milliseconds++;
                    _microseconds = 1000 + (_microseconds - microseconds);
                } else {
                    _microseconds = 0;
                }
            }
            if (milliseconds > 0) {
                _decreaseMilliseconds(milliseconds);
            }
        }

        void CountdownTimer::_decreaseMilliseconds(uint32_t milliseconds)
        {
            uint32_t seconds = milliseconds / 1000;
            milliseconds = milliseconds % 1000;

            if (_milliseconds >= milliseconds) {
                _milliseconds -= milliseconds;
            } else {
                if (_seconds > 0) {
                    seconds++;
                    _milliseconds = 1000 + (_milliseconds - milliseconds);
                } else {
                    _milliseconds = 0;
                }
            }
            if (seconds > 0) {
                _decreaseSeconds(seconds);
            }
        }

        void CountdownTimer::_decreaseSeconds(uint32_t seconds)
        {
            _seconds -= seconds;
        }
    }
}
