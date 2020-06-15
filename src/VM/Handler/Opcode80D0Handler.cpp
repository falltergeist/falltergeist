#include "../../VM/Handler/Opcode80D0Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D0::Opcode80D0(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80D0::_run()
            {
                logger->debug()
                    << "[80D0] [=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus"
                    << ", int min_damage, int max_damage, int attacker_results, int target_results)"
                    << std::endl
                ;

                auto dataStack = _script->dataStack();

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
