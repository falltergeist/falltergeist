#include "Opcode8102.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8102::applyTo(std::shared_ptr<IContext> context)
            {
                auto dataStack = context->dataStack();
                /* auto amount = */ (void) dataStack->pop()->asInteger();
                /* auto trait = */ (void) dataStack->pop()->asInteger();
                /* auto trait_type = */ (void) dataStack->pop()->asInteger();
                /* auto who = */ (void) dataStack->pop()->asObject();
                dataStack->push(0);
            }

            int Opcode8102::number()
            {
                return 0x8102;
            }

            std::string Opcode8102::name()
            {
                return "int critter_add_trait(void* who, int trait_type, int trait, int amount)";
            }

            std::string Opcode8102::notes()
            {
                return "";
            }
        }
    }
}


