#include "../../VM/Handler/Opcode8045.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8045::applyTo(std::shared_ptr<IFalloutContext> context)
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
