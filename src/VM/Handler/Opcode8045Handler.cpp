// Project includes
#include "../../VM/Handler/Opcode8045Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8045::Opcode8045(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8045::_run(VM::Script& script)
            {
                _logger->debug() << "[8045] [*] op_not" << std::endl;
                auto a = script.dataStack()->popLogical();
                script.dataStack()->push((int) (!a));
            }
        }
    }
}
