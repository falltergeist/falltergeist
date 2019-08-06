#include "../../VM/Handler/Opcode8027.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8027::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->pop(); // number of actual arguments
                context->dataStack()->pop(); // getProcedureByIndex index
                // @TODO: compare number of arguments with getProcedureByIndex info and throw script exception if they are not equal
            }

            int Opcode8027::number()
            {
                return 0x8027;
            }

            std::string Opcode8027::name()
            {
                return "op_check_arg_count(int argc, int getProcedureByIndex)";
            }

            std::string Opcode8027::notes()
            {
                return "Maybe push result on stack?";
            }
        }
    }
}
