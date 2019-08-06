#include "../../VM/Handler/Opcode803C.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803C::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->div(bValue));
            }

            int Opcode803C::number()
            {
                return 0x803C;
            }

            std::string Opcode803C::name()
            {
                return "op_div";
            }

            std::string Opcode803C::notes()
            {
                return "";
            }
        }
    }
}
