#include "Opcode8018.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8018::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->swap();
            }

            int Opcode8018::number()
            {
                return 0x8018;
            }

            std::string Opcode8018::name()
            {
                return "void op_swap()";
            }

            std::string Opcode8018::notes()
            {
                return "";
            }
        }
    }
}
