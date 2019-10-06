#include "Opcode802C.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode802C::applyTo(std::shared_ptr<IContext> context)
            {
                context->setScriptVarStackBase(context->dataStack()->size());
            }

            int Opcode802C::number()
            {
                return 0x802C;
            }

            std::string Opcode802C::name()
            {
                return "op_set_global";
            }

            std::string Opcode802C::notes()
            {
                return "";
            }
        }
    }
}
