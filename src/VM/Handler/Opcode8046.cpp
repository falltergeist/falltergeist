#include "../../VM/Handler/Opcode8046.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8046::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto value = context->dataStack()->pop();
                if (value->type() == IFalloutValue::Type::INTEGER) {
                    context->dataStack()->push(-value->asInteger());
                } else if (value->type() == IFalloutValue::Type::FLOAT) {
                    context->dataStack()->push(-value->asFloat());
                } else {
                    // TODO throw exception
                    //_error(std::string("Invalid argument type: ") + value.typeName());
                }
            }

            int Opcode8046::number()
            {
                return 0x8046;
            }

            std::string Opcode8046::name()
            {
                return "op_negate(value)";
            }

            std::string Opcode8046::notes()
            {
                return "";
            }
        }
    }
}
