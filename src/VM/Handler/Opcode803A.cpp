#include "../../VM/Handler/Opcode803A.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803A::applyTo(std::shared_ptr<IFalloutContext> context)
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
