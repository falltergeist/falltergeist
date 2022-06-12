// Project includes
#include "../../VM/Handler/Opcode802AHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802A::Opcode802A(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode802A::_run(VM::Script& script)
            {
                _logger->debug() << "[802A] [*] op_pop_to_base" << std::endl;
                while (script.dataStack()->size() > script.DVARbase()) {
                    script.dataStack()->pop();
                }
            }

        }
    }
}
