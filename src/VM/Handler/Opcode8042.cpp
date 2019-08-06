#include "../../VM/Handler/Opcode8042.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8042::applyTo(std::shared_ptr<IFalloutContext> context)
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
