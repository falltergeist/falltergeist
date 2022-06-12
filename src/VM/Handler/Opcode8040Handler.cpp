// Project includes
#include "../../VM/Handler/Opcode8040Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8040::Opcode8040(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8040::_run(VM::Script& script)
            {
                _logger->debug() << "[8040] [*] op_bwand" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwand: invalid argument types: ") + aValue.typeName() + " bwand " +
                           bValue.typeName());
                }
                script.dataStack()->push(aValue.toInteger() & bValue.toInteger());
            }
        }
    }
}
