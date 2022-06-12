// Project includes
#include "../../VM/Handler/Opcode803DHandler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803D::Opcode803D(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode803D::_run(VM::Script& script)
            {
                _logger->debug() << "[803D] [*] op_mod %" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_mod: invalid argument types: ") + aValue.typeName() + " % " +
                           bValue.typeName());
                }
                script.dataStack()->push(aValue.toInteger() % bValue.toInteger());
            }
        }
    }
}
