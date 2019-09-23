#include "../../VM/Handler/Opcode8129.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8129::applyTo(std::shared_ptr<IFalloutContext> context)
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


