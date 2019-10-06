#include "Opcode8129.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8129::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->pop()->asInteger();
            }

            int Opcode8129::number()
            {
                return 0x8129;
            }

            std::string Opcode8129::name()
            {
                return "void gdialog_mod_barter(int modifier)";
            }

            std::string Opcode8129::notes()
            {
                return "";
            }
        }
    }
}


