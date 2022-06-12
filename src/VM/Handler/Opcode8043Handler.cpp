// Project includes
#include "../../VM/Handler/Opcode8043Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8043::Opcode8043(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8043::_run(VM::Script& script)
            {
                _logger->debug() << "[8043] [*] op_bwnot" << std::endl;
                auto arg = script.dataStack()->pop();
                if (!arg.isNumber()) {
                    _error(std::string("op_bwnot: invalid argument type: ") + arg.typeName());
                }
                script.dataStack()->push(~arg.toInteger());
            }
        }
    }
}
