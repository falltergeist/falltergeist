// Project includes
#include "../../VM/Handler/Opcode80C7Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C7::Opcode80C7(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C7::_run(VM::Script& script)
            {
                _logger->debug() << "[80C7] [*] int script_action()" << std::endl;
                script.dataStack()->push(21);
            }
        }
    }
}
