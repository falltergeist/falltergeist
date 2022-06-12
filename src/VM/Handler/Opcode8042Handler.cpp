// Project includes
#include "../../VM/Handler/Opcode8042Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8042::Opcode8042(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8042::_run(VM::Script& script)
            {
                _logger->debug() << "[8042] [*] op_bwxor" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwxor: invalid argument types: ") + aValue.typeName() + " bwxor " +
                           bValue.typeName());
                }
                script.dataStack()->push(aValue.toInteger() ^ bValue.toInteger());
            }
        }
    }
}
