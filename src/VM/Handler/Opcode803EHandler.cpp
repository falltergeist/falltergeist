// Project includes
#include "../../VM/Handler/Opcode803EHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803E::Opcode803E(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode803E::_run(VM::Script& script)
            {
                _logger->debug() << "[803E] [*] op_and" << std::endl;
                auto b = script.dataStack()->popLogical();
                auto a = script.dataStack()->popLogical();
                script.dataStack()->push(a && b); // integer 1 or 0
            }
        }
    }
}
