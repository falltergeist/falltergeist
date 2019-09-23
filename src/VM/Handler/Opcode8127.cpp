#include "../../VM/Handler/Opcode8127.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8127::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asObject();
            }

            int Opcode8127::number()
            {
                return 0x8127;
            }

            std::string Opcode8127::name()
            {
                return "void critter_injure(ObjectPtr who, int how)";
            }

            std::string Opcode8127::notes()
            {
                return "";
            }
        }
    }
}
