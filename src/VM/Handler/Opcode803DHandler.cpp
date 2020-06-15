#include "../../VM/Handler/Opcode803DHandler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803D::Opcode803D(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode803D::_run()
            {
                logger->debug() << "[803D] [*] op_mod %" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!aValue.isNumber() || !bValue.isNumber()) {
                    _error(std::string("op_mod: invalid argument types: ") + aValue.typeName() + " % " +
                           bValue.typeName());
                }
                _script->dataStack()->push(aValue.toInteger() % bValue.toInteger());
            }
        }
    }
}
