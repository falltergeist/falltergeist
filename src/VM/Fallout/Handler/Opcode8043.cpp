#include "Opcode8043.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8043::applyTo(std::shared_ptr<IContext> context)
            {
                auto arg = context->dataStack()->pop();
                context->dataStack()->push(~arg->asInteger());
            }

            int Opcode8043::number()
            {
                return 0x8043;
            }

            std::string Opcode8043::name()
            {
                return "int op_bwnot(int a)";
            }

            std::string Opcode8043::notes()
            {
                return "";
            }
        }
    }
}
