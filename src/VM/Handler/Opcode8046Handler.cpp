// Project includes
#include "../../VM/Handler/Opcode8046Handler.h"
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
            Opcode8046::Opcode8046(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8046::_run()
            {
                logger->debug() << "[8046] [*] op_negate" << std::endl;
                auto value = _script->dataStack()->pop();
                if (value.type() == StackValue::Type::INTEGER) {
                    _script->dataStack()->push(-value.integerValue());
                } else if (value.type() == StackValue::Type::FLOAT) {
                    _script->dataStack()->push(-value.floatValue());
                } else {
                    _error(std::string("Invalid argument type: ") + value.typeName());
                }
            }
        }
    }
}
