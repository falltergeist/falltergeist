#include "../Game/Game.h"
#include "../Game/GameTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        GameTimer::GameTimer(unsigned interval) : AbstractTimer(interval)
        {
            _time = Game::getInstance()->gameTime();
        }

        unsigned int GameTimer::_getTime()
        {
            return _time->ticks();
        }
    }
}
