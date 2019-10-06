#include "Opcode803F.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803F::applyTo(std::shared_ptr<IContext> context)
            {
                auto b = (bool) context->dataStack()->pop()->asInteger();
                auto a = (bool) context->dataStack()->pop()->asInteger();
                context->dataStack()->push((int)(a || b)); // integer 1 or 0
            }

            int Opcode803F::number()
            {
                return 0x803F;
            }

            std::string Opcode803F::name()
            {
                return "op_or";
            }

            std::string Opcode803F::notes()
            {
                return "";
            }
        }
    }
}
