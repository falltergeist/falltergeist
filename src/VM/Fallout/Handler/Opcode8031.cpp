#include "Opcode8031.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8031::applyTo(std::shared_ptr<IContext> context)
            {
                auto num = context->dataStack()->pop()->asInteger();
                auto value = context->dataStack()->pop();
                context->dataStack()->at(context->dynamicVarStackBase() + num) = value;
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
