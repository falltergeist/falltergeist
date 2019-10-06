#include "Opcode80C7.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C7::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->push(21);
            }

            int Opcode80C7::number()
            {
                return 0x80C7;
            }

            std::string Opcode80C7::name()
            {
                return "int script_action()";
            }

            std::string Opcode80C7::notes()
            {
                return "";
            }
        }
    }
}
