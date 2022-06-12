// Project includes
#include "../../VM/Handler/Opcode8041Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8041::Opcode8041(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8041::_run(VM::Script& script)
            {
                _logger->debug() << "[8041] [*] op_bwor" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwor: invalid argument types: ") + aValue.typeName() + " bwor " +
                           bValue.typeName());
                }
                script.dataStack()->push(aValue.toInteger() | bValue.toInteger());
            }
        }
    }
}
