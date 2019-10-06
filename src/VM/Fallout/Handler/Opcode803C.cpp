#include "Opcode803C.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803C::applyTo(std::shared_ptr<IContext> context)
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
