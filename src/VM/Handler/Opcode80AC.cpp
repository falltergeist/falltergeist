#include "../../VM/Handler/Opcode80AC.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AC::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto dataStack = context->dataStack();
                dataStack->pop()->asInteger();
                dataStack->pop()->asInteger();
                dataStack->pop()->asObject();
                dataStack->push((int)2);
            }

            int Opcode80AC::number()
            {
                return 0x80AC;
            }

            std::string Opcode80AC::name()
            {
                return "int roll_vs_skill(ObjectPtr who, int skill, int modifier)";
            }

            std::string Opcode80AC::notes()
            {
                return "";
            }
        }
    }
}
