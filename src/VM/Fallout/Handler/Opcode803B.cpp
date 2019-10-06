#include "Opcode803B.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803B::applyTo(std::shared_ptr<IContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->mul(bValue));
            }

            int Opcode803B::number()
            {
                return 0x803B;
            }

            std::string Opcode803B::name()
            {
                return "op_mul(a, b)";
            }

            std::string Opcode803B::notes()
            {
                return "";
            }
        }
    }
}
