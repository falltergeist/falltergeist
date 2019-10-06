#include <cstdlib>
#include "Opcode80B4.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B4::applyTo(std::shared_ptr<IContext> context)
            {
                auto max = context->dataStack()->pop()->asInteger();
                auto min = context->dataStack()->pop()->asInteger();
                context->dataStack()->push((int)(rand() % (max - min + 1) + min));
            }

            int Opcode80B4::number()
            {
                return 0x80B4;
            }

            std::string Opcode80B4::name()
            {
                return "int rand(int min, int max)";
            }

            std::string Opcode80B4::notes()
            {
                return "";
            }
        }
    }
}


