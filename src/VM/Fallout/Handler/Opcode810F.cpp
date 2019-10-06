#include "Opcode810F.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810F::applyTo(std::shared_ptr<IContext> context)
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


