#include "Opcode80C2.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C2::applyTo(std::shared_ptr<IContext> context)
            {
                auto value = context->dataStack()->pop();
                unsigned int num = context->dataStack()->pop()->asInteger();
                while (num >= context->LVARS()->size()) {
                    context->LVARS()->push_back(StackValue(0));
                }
                context->LVARS()->at(num) = value;
            }

            int Opcode80C2::number()
            {
                return 0x80C2;
            }

            std::string Opcode80C2::name()
            {
                return "LVAR[num] = value";
            }

            std::string Opcode80C2::notes()
            {
                return "";
            }
        }
    }
}


