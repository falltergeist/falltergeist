// Project includes
#include "../../VM/Handler/Opcode803BHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803B::Opcode803B(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode803B::_run(VM::Script& script)
            {
                _logger->debug() << "[803B] [*] op_mul(a, b) *" << std::endl;
                auto bValue = script.dataStack()->pop();
                auto aValue = script.dataStack()->pop();
                if (!bValue.isNumber() || !aValue.isNumber()) {
                    _error(std::string("op_mul(a, b): Incompatible types: ") + aValue.typeName() + " * " +
                           bValue.typeName());
                }
                if (aValue.type() == StackValue::Type::INTEGER) {
                    if (bValue.type() == StackValue::Type::INTEGER) {
                        script.dataStack()->push(aValue.integerValue() * bValue.integerValue());
                    } else {
                        script.dataStack()->push((float) aValue.integerValue() * bValue.floatValue());
                    }
                } else {
                    if (bValue.type() == StackValue::Type::INTEGER) {
                        script.dataStack()->push(aValue.floatValue() * (float) bValue.integerValue());
                    } else {
                        script.dataStack()->push(aValue.floatValue() * bValue.floatValue());
                    }
                }
            }
        }
    }
}
