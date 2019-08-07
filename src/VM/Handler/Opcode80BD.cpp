#include "../../VM/Handler/Opcode80BD.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BD::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // TODO
                //context->dataStack()->push(context->sourceObject());
            }

            int Opcode80BD::number()
            {
                return 0x80BD;
            }

            std::string Opcode80BD::name()
            {
                return "void* source_obj()";
            }

            std::string Opcode80BD::notes()
            {
                return "";
            }
        }
    }
}


