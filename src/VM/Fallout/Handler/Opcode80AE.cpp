#include "Opcode80AE.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AE::applyTo(std::shared_ptr<IContext> context)
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


