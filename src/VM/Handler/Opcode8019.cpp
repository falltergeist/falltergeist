#include "../../VM/Handler/Opcode8019.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8019::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->returnStack()->swap();
            }

            int Opcode8019::number()
            {
                return 0x8019;
            }

            std::string Opcode8019::name()
            {
                return "void op_swapa()";
            }

            std::string Opcode8019::notes()
            {
                return "";
            }
        }
    }
}
