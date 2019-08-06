#include "../../VM/Handler/Opcode8030.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8030::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto condition = context->dataStack()->pop()->asInteger();
                if (!condition) {
                    context->setProgramCounter(context->dataStack()->pop()->asInteger());
                }
            }

            int Opcode8030::number()
            {
                return 0x8030;
            }

            std::string Opcode8030::name()
            {
                return "void op_while(bool condition, int address)";
            }

            std::string Opcode8030::notes()
            {
                return "";
            }
        }
    }
}
