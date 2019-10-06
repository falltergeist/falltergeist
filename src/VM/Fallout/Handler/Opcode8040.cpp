#include "Opcode8040.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8040::applyTo(std::shared_ptr<IContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->asInteger() & bValue->asInteger());
            }

            int Opcode8040::number()
            {
                return 0x8040;
            }

            std::string Opcode8040::name()
            {
                return "int op_bwand (int a, int b)";
            }

            std::string Opcode8040::notes()
            {
                return "";
            }
        }
    }
}
