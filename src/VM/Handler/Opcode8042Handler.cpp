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
            Opcode8042::Opcode8042(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8042::_run()
            {
                logger->debug() << "[8042] [*] op_bwxor" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwxor: invalid argument types: ") + aValue.typeName() + " bwxor " +
                           bValue.typeName());
                }
                _script->dataStack()->push(aValue.toInteger() ^ bValue.toInteger());
            }
        }
    }
}
