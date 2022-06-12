// Project includes
#include "../../VM/Handler/Opcode8134Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8134::Opcode8134(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8134::_run(VM::Script& script)
            {
                _logger->debug() << "[8134] [=] void game_ui_enable()" << std::endl;
            }
        }
    }
}
