#include "Opcode80D0Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D0::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT")
                        << "[80D0] [=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus"
                           ", int min_damage, int max_damage, int attacker_results, int target_results)" << std::endl;

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
