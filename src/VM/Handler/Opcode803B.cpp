#include "../../VM/Handler/Opcode803B.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803B::applyTo(std::shared_ptr<IFalloutContext> context)
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
