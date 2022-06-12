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
            Opcode8046::Opcode8046(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8046::_run(VM::Script& script)
            {
                _logger->debug() << "[8046] [*] op_negate" << std::endl;
                auto value = script.dataStack()->pop();
                if (value.type() == StackValue::Type::INTEGER) {
                    script.dataStack()->push(-value.integerValue());
                } else if (value.type() == StackValue::Type::FLOAT) {
                    script.dataStack()->push(-value.floatValue());
                } else {
                    _error(std::string("Invalid argument type: ") + value.typeName());
                }
            }
        }
    }
}
