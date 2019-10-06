#include "Opcode8128.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8128::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->push(0);
            }

            int Opcode8128::number()
            {
                return 0x8128;
            }

            std::string Opcode8128::name()
            {
                return "int combat_is_initialized()";
            }

            std::string Opcode8128::notes()
            {
                return "";
            }
        }
    }
}
