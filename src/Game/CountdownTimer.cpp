#include "../Game/CountdownTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        CountdownTimer::CountdownTimer(uint32_t seconds, uint32_t milliseconds)
        {
            _seconds = seconds;
            _milliseconds = milliseconds;
        }

        void CountdownTimer::think(float deltaTime)
        {
            if (isFinished()) {
                return;
            }

            uint32_t seconds = 0;

            while (deltaTime >= 1000.0f) {
                seconds++;
                deltaTime -= 1000.0f;
            }

            if (_milliseconds >= deltaTime) {
                _milliseconds -= deltaTime;
            } else {
                if (_seconds > seconds) {
                    seconds++;
                    _milliseconds = 1000 + (_milliseconds - deltaTime);
                } else {
                    _milliseconds = 0;
                }
            }
            _decreaseSeconds(seconds);
        }

        bool CountdownTimer::isFinished()
        {
            return _seconds == 0 && _milliseconds == 0;
        }

        void CountdownTimer::_decreaseSeconds(uint32_t seconds)
        {
            if (_seconds >= seconds) {
                _seconds -= seconds;
            } else {
                _seconds = 0;
            }
        }
    }
}
