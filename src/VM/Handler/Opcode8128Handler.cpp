// Project includes
#include "../../VM/Handler/Opcode8128Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8128::Opcode8128(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8128::_run(VM::Script& script)
            {
                _logger->debug() << "[8128] [=] int combat_is_initialized()" << std::endl;
                script.dataStack()->push(0);
            }
        }
    }
}
