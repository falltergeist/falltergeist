#include "Opcode801C.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode801C::applyTo(std::shared_ptr<IContext> context)
            {
                context->setProgramCounter((unsigned) context->returnStack()->pop()->asInteger());
            }

            int Opcode801C::number()
            {
                return 0x801C;
            }

            std::string Opcode801C::name()
            {
                return "op_pop_return";
            }

            std::string Opcode801C::notes()
            {
                return "";
            }
        }
    }
}
