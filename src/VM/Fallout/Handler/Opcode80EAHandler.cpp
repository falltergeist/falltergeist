#include "Opcode80EAHandler.h"
#include "Game/Game.h"
#include "Game/Time.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80EA::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80EA] [*] int gameTime()" << std::endl;
                _script->dataStack()->push((int) Game::getInstance()->gameTime()->ticks());
            }
        }
    }
}


