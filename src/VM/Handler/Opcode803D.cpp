#include "../../VM/Handler/Opcode803D.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode803D::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto bValue = context->dataStack()->pop();
                auto aValue = context->dataStack()->pop();
                context->dataStack()->push(aValue->asInteger() % bValue->asInteger());
            }

            int Opcode803D::number()
            {
                return 0x803D;
            }

            std::string Opcode803D::name()
            {
                return "op_mod %";
            }

            std::string Opcode803D::notes()
            {
                return "";
            }
        }
    }
}
