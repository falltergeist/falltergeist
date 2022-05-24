// Project includes
#include "../../VM/Handler/Opcode803CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803C::Opcode803C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode803C::_run()
            {
                logger->debug() << "[803C] [*] op_div /" << std::endl;
                auto bValue = _script->dataStack()->pop();
                auto aValue = _script->dataStack()->pop();
                if (!bValue.isNumber() || !aValue.isNumber()) {
                    _error(std::string("op_div(a, b): Incompatible types: ") + aValue.typeName() + " / " +
                           bValue.typeName());
                }
                if (aValue.type() == StackValue::Type::INTEGER) {
                    if (bValue.type() == StackValue::Type::INTEGER) {
                        _script->dataStack()->push(aValue.integerValue() / bValue.integerValue());
                    } else {
                        _script->dataStack()->push((float) aValue.integerValue() / bValue.floatValue());
                    }
                } else {
                    if (bValue.type() == StackValue::Type::INTEGER) {
                        _script->dataStack()->push(aValue.floatValue() / (float) bValue.integerValue());
                    } else {
                        _script->dataStack()->push(aValue.floatValue() / bValue.floatValue());
                    }
                }
            }
        }
    }
}
