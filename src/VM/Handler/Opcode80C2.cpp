#include "../../VM/Handler/Opcode80C2.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C2::applyTo(std::shared_ptr<IFalloutContext> context)
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


