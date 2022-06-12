// Project includes
#include "../../VM/Handler/Opcode8118Handler.h"
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
            Opcode8118::Opcode8118(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8118::_run(VM::Script& script)
            {
                _logger->debug() << "[8118] [*] int get_month" << std::endl;
                script.dataStack()->push(Game::Game::getInstance()->gameTime()->month());
            }
        }
    }
}
