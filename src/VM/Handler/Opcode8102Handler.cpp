// Project includes
#include "../../VM/Handler/Opcode8102Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8102::Opcode8102(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8102::_run(VM::Script& script) {
                _logger->debug()
                    << "[8102] [*] int critter_add_trait(void* who, int trait_type, int trait, int amount) "
                    << std::endl
                ;
                auto dataStack = script.dataStack();
                /* auto amount = */ (void) dataStack->popInteger();
                /* auto trait = */ (void) dataStack->popInteger();
                /* auto trait_type = */ (void) dataStack->popInteger();
                /* auto who = */ (void) dataStack->popObject();
                dataStack->push(0);
            }
        }
    }
}


