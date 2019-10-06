#include "Opcode801B.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode801B::applyTo(std::shared_ptr<IContext> context)
            {
                // TODO clone value
                context->dataStack()->push(context->dataStack()->top());
            }

            int Opcode801B::number()
            {
                return 0x801B;
            }

            std::string Opcode801B::name()
            {
                return "op_dup";
            }

            std::string Opcode801B::notes()
            {
                return "";
            }
        }
    }
}
