#include "../../VM/Handler/Opcode801A.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode801A::applyTo(std::shared_ptr<IFalloutContext> context)
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
