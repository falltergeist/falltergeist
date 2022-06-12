// Project includes
#include "../../VM/Handler/Opcode802CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802C::Opcode802C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode802C::_run(VM::Script& script)
            {
                script.setSVARbase(static_cast<int>(script.dataStack()->size()));
                _logger->debug() << "[802C] [*] op_set_global = " << script.SVARbase() << std::endl;
            }
        }
    }
}
