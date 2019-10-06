#include "Opcode8041.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void applyTo(std::shared_ptr<IContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->asInteger() | bValue->asInteger());
            }

            int Opcode8041::number()
            {
                return 0x8041;
            }

            std::string Opcode8041::name()
            {
                return "int op_bwor(int a, int b)";
            }

            std::string Opcode8041::notes()
            {
                return "";
            }
        }
    }
}
