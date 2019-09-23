#include "../../VM/Handler/Opcode810F.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810F::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asObject();
            }

            int Opcode810F::number()
            {
                return 0x810F;
            }

            std::string Opcode810F::name()
            {
                return "void reg_anim_animate(void* what, int anim, int delay)";
            }

            std::string Opcode810F::notes()
            {
                return "";
            }
        }
    }
}


