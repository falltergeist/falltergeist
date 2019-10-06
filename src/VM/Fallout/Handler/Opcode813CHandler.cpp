#include "Opcode813CHandler.h"
#include "Game/CritterObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode813C::applyTo(std::shared_ptr<IContext> context)
            {
                int amount = _script->dataStack()->popInteger();
                int skill = _script->dataStack()->popInteger();
                auto critter = static_cast<Game::CritterObject *>(_script->dataStack()->popObject());

                critter->setSkillGainedValue((SKILL) skill, critter->skillGainedValue((SKILL) skill) + amount);

                Logger::debug("SCRIPT")
                        << "[813C] void critter_mod_skill(GameCritterObject* who, int skill, int amount)" << std::endl
                        << "    skill = " << skill << std::endl
                        << "    amount = " << amount << std::endl;
            }
        }
    }
}
