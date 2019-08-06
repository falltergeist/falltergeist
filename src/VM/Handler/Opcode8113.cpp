#include "../../VM/Handler/Opcode8113.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8113::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->pop()->asInteger(); // -1
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asObject();
            }

            int Opcode8113::number()
            {
                return 0x8113;
            }

            std::string Opcode8113::name()
            {
                return "void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)";
            }

            std::string Opcode8113::notes()
            {
                return "";
            }
        }
    }
}
