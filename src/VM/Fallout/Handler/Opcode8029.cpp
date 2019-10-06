#include "Opcode8029.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8029::applyTo(std::shared_ptr<IContext> context)
            {
                context->setDynamicVarStackBase(context->returnStack()->pop()->asInteger());
            }

            int Opcode8029::number()
            {
                return 0x8029;
            }

            std::string Opcode8029::name()
            {
                return "void op_pop_base()";
            }

            std::string Opcode8029::notes()
            {
                return "";
            }
        }
    }
}
