#include "../../Game/CritterObject.h"
#include "../../VM/Handler/Opcode80BC.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BC::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // TODO
                //context->dataStack()->push(context->owner());
            }

            int Opcode80BC::number()
            {
                return 0x80BC;
            }

            std::string Opcode80BC::name()
            {
                return "GameObject* self_obj()";
            }

            std::string Opcode80BC::notes()
            {
                return "";
            }
        }
    }
}
