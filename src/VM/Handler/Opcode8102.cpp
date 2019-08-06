#include "../../VM/Handler/Opcode8102.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8102::applyTo(std::shared_ptr<IFalloutContext> context)
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


