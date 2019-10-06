#include "Opcode8032.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8032::applyTo(std::shared_ptr<IContext> context)
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
