#include "Opcode8042.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8042::applyTo(std::shared_ptr<IContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->asInteger() ^ bValue->asInteger());
            }

            int Opcode8042::number()
            {
                return 0x8042;
            }

            std::string Opcode8042::name()
            {
                return "int op_bwxor(int a, int b)";
            }

            std::string Opcode8042::notes()
            {
                return "";
            }
        }
    }
}
