#include "../../VM/Handler/Opcode813CHandler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode813C::Opcode813C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode813C::_run()
            {
                int amount = _script->dataStack()->popInteger();
                int skill = _script->dataStack()->popInteger();
                auto critter = static_cast<Game::CritterObject *>(_script->dataStack()->popObject());

                critter->setSkillGainedValue((SKILL) skill, critter->skillGainedValue((SKILL) skill) + amount);

                logger->debug()
                    << "[813C] void critter_mod_skill(GameCritterObject* who, int skill, int amount)" << std::endl
                    << "    skill = " << skill << std::endl
                    << "    amount = " << amount << std::endl
                ;
            }
        }
    }
}
