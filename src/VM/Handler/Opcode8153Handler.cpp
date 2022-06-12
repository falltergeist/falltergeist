// Project includes
#include "../../VM/Handler/Opcode8153Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8153::Opcode8153(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8153::_run(VM::Script& script)
            {
                _logger->debug() << "[8153] [=] void terminate_combat()" << std::endl;
            }
        }
    }
}
