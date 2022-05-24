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
            Opcode8041::Opcode8041(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8041::_run()
            {
                logger->debug() << "[8041] [*] op_bwor" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwor: invalid argument types: ") + aValue.typeName() + " bwor " +
                           bValue.typeName());
                }
                _script->dataStack()->push(aValue.toInteger() | bValue.toInteger());
            }
        }
    }
}
