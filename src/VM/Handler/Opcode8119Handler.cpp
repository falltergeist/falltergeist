// Project includes
#include "../../VM/Handler/Opcode8119Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8119::Opcode8119(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8119::_run()
            {
                _script->dataStack()->push(Game::Game::getInstance()->gameTime()->day());
                logger->debug() << "[8119] [*] int get_day()" << std::endl;
            }
        }
    }
}
