#include "../Game/CountdownTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        CountdownTimer::CountdownTimer(uint32_t milliseconds)
        {
            _milliseconds = milliseconds;
        }

        void CountdownTimer::think(const float &deltaTime)
        {
            if (isFinished()) {
                return;
            }

            if (_milliseconds >= static_cast<uint32_t>(deltaTime)) {
                _milliseconds -= static_cast<uint32_t>(deltaTime);
            } else {
                _milliseconds = 0;
            }
        }

        bool CountdownTimer::isFinished()
        {
            return _milliseconds == 0;
        }

        void CountdownTimer::set(uint32_t milliseconds)
        {
            _milliseconds = milliseconds;
        }

        uint32_t CountdownTimer::get() const
        {
            return _milliseconds;
        }
    }
}
