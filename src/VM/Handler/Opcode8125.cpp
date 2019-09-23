#include "../../VM/Handler/Opcode8125.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8125::applyTo(std::shared_ptr<IFalloutContext> context)
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
