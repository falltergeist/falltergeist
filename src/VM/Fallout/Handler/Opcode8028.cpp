#include "Opcode8028.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IProcedure.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8028::applyTo(std::shared_ptr<IContext> context)
            {
                std::string name = context->dataStack()->pop()->asString();
                context->dataStack()->push((int) context->getProcedureByName(name)->bodyOffset());
            }

            int Opcode8028::number()
            {
                return 0x8028;
            }

            std::string Opcode8028::name()
            {
                return "int lookup_string_proc(string getProcedureByIndex)";
            }

            std::string Opcode8028::notes()
            {
                return "returns getProcedureByIndex address";
            }
        }
    }
}
