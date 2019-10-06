#include "Opcode80B0.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B0::applyTo(std::shared_ptr<IContext> context)
            {
                auto value = context->dataStack()->pop()->asInteger();
                if (value == 0 || value == 3) {
                    context->dataStack()->push((int)1);
                } else {
                    context->dataStack()->push((int)0);
                }
            }

            int Opcode80B0::number()
            {
                return 0x80B0;
            }

            std::string Opcode80B0::name()
            {
                return "int is_critical(int val)";
            }

            std::string Opcode80B0::notes()
            {
                return "";
            }
        }
    }
}


