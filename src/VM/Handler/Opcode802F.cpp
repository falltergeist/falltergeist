#include "../../VM/Handler/Opcode802F.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/IFalloutContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode802F::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto condition = context->dataStack()->pop()->asInteger();
                auto address = context->dataStack()->pop()->asInteger();
                if (!condition) {
                    context->setProgramCounter(address);
                }
            }

            int Opcode802F::number()
            {
                return 0x802F;
            }

            std::string Opcode802F::name()
            {
                return "op_if(address, condition)";
            }

            std::string Opcode802F::notes()
            {
                return "";
            }
        }
    }
}
