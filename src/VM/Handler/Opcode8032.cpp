#include "../../VM/Handler/Opcode8032.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8032::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto num = context->dataStack()->pop()->asInteger();
                auto value = context->dataStack()->at(context->dynamicVarStackBase() + num);
                context->dataStack()->push(value);
            }

            int Opcode8032::number()
            {
                return 0x8032;
            }

            std::string Opcode8032::name()
            {
                return "mixed op_fetch(int number)";
            }

            std::string Opcode8032::notes()
            {
                return "";
            }
        }
    }
}
