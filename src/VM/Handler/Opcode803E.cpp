#include "../../VM/Handler/Opcode803E.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803E::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto b = (bool) context->dataStack()->pop()->asInteger();
                auto a = (bool) context->dataStack()->pop()->asInteger();
                context->dataStack()->push((int)(a && b)); // integer 1 or 0
            }

            int Opcode803E::number()
            {
                return 0x803E;
            }

            std::string Opcode803E::name()
            {
                return "op_and";
            }

            std::string Opcode803E::notes()
            {
                return "";
            }
        }
    }
}
