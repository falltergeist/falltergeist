#include "../../VM/Handler/Opcode800D.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode800D::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->returnStack()->push(context->dataStack()->pop());
            }

            int Opcode800D::number()
            {
                return 0x800D;
            }

            std::string Opcode800D::name()
            {
                return "op_d_to_a";
            }

            std::string Opcode800D::notes()
            {
                return "";
            }
        }
    }
}
