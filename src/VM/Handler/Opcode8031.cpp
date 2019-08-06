#include "../../VM/Handler/Opcode8031.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8031::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto num = context->dataStack()->popInteger();
                auto value = context->dataStack()->pop();
                _script->dataStack()->values()->at(_script->DVARbase() + num) = value;
            }

            int Opcode8031::number()
            {
                return 0x8031;
            }

            std::string Opcode8031::name()
            {
                return "void op_store(int num, mixed value)";
            }

            std::string Opcode8031::notes()
            {
                return "";
            }
        }
    }
}
