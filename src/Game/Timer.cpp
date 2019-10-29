#include <SDL.h>
#include "../Game/Timer.h"

namespace Falltergeist
{
    namespace Game
    {
        Timer::Timer(unsigned interval) : AbstractTimer(interval)
        {
        }

        unsigned int Timer::_getTime()
        {
            return SDL_GetTicks();
        }
    }
}
