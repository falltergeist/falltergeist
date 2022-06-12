// Project includes
#include "../../VM/Handler/Opcode803FHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803F::Opcode803F(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode803F::_run(VM::Script& script)
            {
                _logger->debug() << "[803F] [+] op_or" << std::endl;
                auto b = script.dataStack()->popLogical();
                auto a = script.dataStack()->popLogical();
                script.dataStack()->push(a || b); // integer 1 or 0
            }
        }
    }
}
