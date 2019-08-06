#include "../../VM/Handler/Opcode8041.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void applyTo(std::shared_ptr<IFalloutContext> context)
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
