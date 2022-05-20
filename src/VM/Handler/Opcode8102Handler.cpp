#include "../../VM/Handler/Opcode8102Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8102::Opcode8102(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8102::_run() {
                logger->debug()
                    << "[8102] [*] int critter_add_trait(void* who, int trait_type, int trait, int amount) "
                    << std::endl
                ;
                auto dataStack = _script->dataStack();
                /* auto amount = */ (void) dataStack->popInteger();
                /* auto trait = */ (void) dataStack->popInteger();
                /* auto trait_type = */ (void) dataStack->popInteger();
                /* auto who = */ (void) dataStack->popObject();
                dataStack->push(0);
            }
        }
    }
}


