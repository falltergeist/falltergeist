#include "Opcode8125.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8125::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->pop()->asObject();
            }

            int Opcode8125::number()
            {
                return 0x8125;
            }

            std::string Opcode8125::name()
            {
                return "void party_remove(void* who)";
            }

            std::string Opcode8125::notes()
            {
                return "";
            }
        }
    }
}
