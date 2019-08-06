#include "../../VM/Handler/Opcode8044.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8044::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto value = context->dataStack()->pop();
                int result = 0;
                if (value->type() == IFalloutValue::Type::FLOAT) {
                    result = (int) value->asFloat(); // this is how "floor" originally worked..
                } else if (value->type() == IFalloutValue::Type::INTEGER) {
                    result = value->asInteger();
                } else {
                    // TODO throw Exception
                    //_error(std::string("op_floor: invalid argument type: ") + value.typeName());
                }
                context->dataStack()->push(result);
            }

            int Opcode8044::number()
            {
                return 0x8044;
            }

            std::string Opcode8044::name()
            {
                return "int op_floor(value)";
            }

            std::string Opcode8044::notes()
            {
                return "";
            }
        }
    }
}
