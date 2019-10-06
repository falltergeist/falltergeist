#include "../../../VM/Fallout/Handler/Opcode800C.h"
#include "../../../VM/Fallout/IContext.h"
#include "../../../VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode800C::applyTo(std::shared_ptr<IContext>& context)
                {
                    context->dataStack()->push(context->returnStack()->pop());
                }

                int Opcode800C::number()
                {
                    return 0x800C;
                }

                std::string Opcode800C::name()
                {
                    return "op_a_to_d";
                }

                std::string Opcode800C::notes() {
                    return "";
                }
            }
        }
    }
}
