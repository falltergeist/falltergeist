#include "../../VM/Handler/Opcode802C.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode802C::applyTo(std::shared_ptr<IFalloutContext> context)
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
