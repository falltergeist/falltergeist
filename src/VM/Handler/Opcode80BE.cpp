#include "../../VM/Handler/Opcode80BE.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BE::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                //context->dataStack()->push(context->targetObject());
            }

            int Opcode80BE::number()
            {
                return 0x80BE;
            }

            std::string Opcode80BE::name()
            {
                return "object target_obj/obj_being_used_with()";
            }

            std::string Opcode80BE::notes()
            {
                return "";
            }
        }
    }
}
