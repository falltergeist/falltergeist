#include "../../VM/Handler/Opcode801B.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode801B::applyTo(std::shared_ptr<IFalloutContext> context)
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
