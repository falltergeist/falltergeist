#include "../../VM/Handler/Opcode80AE.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AE::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto dataStack = context->dataStack();
                dataStack->pop()->asInteger();
                dataStack->pop()->asInteger();
                dataStack->pop()->asObject();
                dataStack->push((int)2);
            }

            int Opcode80AE::number()
            {
                return 0x80AE;
            }

            std::string Opcode80AE::name()
            {
                return "int do_check(ObjectPtr who, int check, int modifier)";
            }

            std::string Opcode80AE::notes()
            {
                return "";
            }
        }
    }
}


