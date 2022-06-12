// Project includes
#include "../../VM/Handler/Opcode8133Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8133::Opcode8133(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8133::_run(VM::Script& script)
            {
                _logger->debug() << "[8134] [=] void game_ui_disable()" << std::endl;
            }
        }
    }
}
