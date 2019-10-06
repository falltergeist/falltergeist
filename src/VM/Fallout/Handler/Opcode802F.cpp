#include "Opcode802F.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode802F::applyTo(std::shared_ptr<IContext> context)
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
