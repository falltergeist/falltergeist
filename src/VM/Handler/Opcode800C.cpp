#include "../../VM/Handler/Opcode800C.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode800C::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->push(context->returnStack()->pop());
            }

            int Opcode800C::number()
            {
                return 0x800C;
            }

            std::string Opcode800C::name()
            {
                return "op_a_to_d";
            }

            std::string Opcode800C::notes() {
                return "";
            }
        }
    }
}
