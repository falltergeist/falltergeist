#include "../Game/Game.h"
#include "../Game/GameTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        GameTimer::GameTimer(float interval) : AbstractTimer(interval * 10)
        {
        }
    }
}
