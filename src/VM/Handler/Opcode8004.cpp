#include "../../VM/Handler/Opcode8004.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8004::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto address = context->dataStack()->pop()->asInteger();
                context->setProgramCounter((unsigned) address);
            }

            int Opcode8004::number()
            {
                return 0x8004;
            }

            std::string Opcode8004::name()
            {
                return "void op_jmp(int address)";
            }

            std::string Opcode8004::notes()
            {
                return "Implemented";
            }
        }
    }
}
