#include <cstdlib>
#include "../../VM/Handler/Opcode80B4.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B4::applyTo(std::shared_ptr<IFalloutContext> context)
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


