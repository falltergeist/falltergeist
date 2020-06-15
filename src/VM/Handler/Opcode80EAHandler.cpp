#include "../../VM/Handler/Opcode80EAHandler.h"
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80EA::Opcode80EA(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80EA::_run()
            {
                logger->debug() << "[80EA] [*] int gameTime()" << std::endl;
                _script->dataStack()->push((int) Game::Game::getInstance()->gameTime()->ticks());
            }
        }
    }
}


