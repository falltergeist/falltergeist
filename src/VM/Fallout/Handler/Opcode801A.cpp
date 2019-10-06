#include "Opcode801A.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode801A::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->pop();
            }

            int Opcode801A::number()
            {
                return 0x801A;
            }

            std::string Opcode801A::name()
            {
                return "op_pop";
            }

            std::string Opcode801A::notes()
            {
                return "";
            }
        }
    }
}
