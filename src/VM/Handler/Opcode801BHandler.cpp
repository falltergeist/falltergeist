// Project includes
#include "../../VM/Handler/Opcode801BHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801B::Opcode801B(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode801B::_run(VM::Script& script)
            {
                _logger->debug() << "[801B] op_dup" << std::endl;
                script.dataStack()->push(script.dataStack()->top());
            }
        }
    }
}
