#include "../../VM/Handler/Opcode8040Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8040::Opcode8040(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8040::_run()
            {
                logger->debug() << "[8040] [*] op_bwand" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_bwand: invalid argument types: ") + aValue.typeName() + " bwand " +
                           bValue.typeName());
                }
                _script->dataStack()->push(aValue.toInteger() & bValue.toInteger());
            }
        }
    }
}
