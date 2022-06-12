// Project includes
#include "../../VM/Handler/Opcode80D0Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D0::Opcode80D0(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D0::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80D0] [=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus"
                    << ", int min_damage, int max_damage, int attacker_results, int target_results)"
                    << std::endl
                ;

                auto dataStack = script.dataStack();

                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popObject();
            }
        }
    }
}
