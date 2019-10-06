#include "Opcode802B.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode802B::applyTo(std::shared_ptr<IContext> context)
            {
                auto argumentsCounter = context->dataStack()->pop()->asInteger();
                context->returnStack()->push((int)context->dynamicVarStackBase());
                context->setDynamicVarStackBase(context->dataStack()->size() - argumentsCounter);
            }

            int Opcode802B::number()
            {
                return 0x802B;
            }

            std::string Opcode802B::name()
            {
                return "op_push_base";
            }

            std::string Opcode802B::notes()
            {
                return "";
            }
        }
    }
}
