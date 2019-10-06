#include "Opcode8045.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8045::applyTo(std::shared_ptr<IContext> context)
            {
                auto a = (bool) context->dataStack()->pop()->asInteger();
                context->dataStack()->push((int) (!a));
            }

            int Opcode8045::number()
            {
                return 0x8045;
            }

            std::string Opcode8045::name()
            {
                return "op_not";
            }

            std::string Opcode8045::notes()
            {
                return "";
            }
        }
    }
}
