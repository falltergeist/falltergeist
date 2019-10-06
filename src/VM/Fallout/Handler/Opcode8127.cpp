#include "Opcode8127.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8127::applyTo(std::shared_ptr<IContext> context)
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
