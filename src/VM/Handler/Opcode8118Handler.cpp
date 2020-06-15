#include "../../VM/Handler/Opcode8118Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8118::Opcode8118(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8118::_run()
            {
                logger->debug() << "[8118] [*] int get_month" << std::endl;
                _script->dataStack()->push(Game::Game::getInstance()->gameTime()->month());
            }
        }
    }
}
