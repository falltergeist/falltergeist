#include "Opcode803A.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803A::applyTo(std::shared_ptr<IContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->sub(bValue));
            }

            int Opcode803A::number()
            {
                return 0x803A;
            }

            std::string Opcode803A::name()
            {
                return "op_sub(a, b)";
            }

            std::string Opcode803A::notes()
            {
                return "";
            }
        }
    }
}
