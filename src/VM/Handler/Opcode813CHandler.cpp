// Project includes
#include "../../VM/Handler/Opcode813CHandler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode813C::Opcode813C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode813C::_run(VM::Script& script)
            {
                int amount = script.dataStack()->popInteger();
                int skill = script.dataStack()->popInteger();
                auto critter = static_cast<Game::CritterObject *>(script.dataStack()->popObject());

                critter->skillCollection()->setSkillGainedValue((SKILL) skill, critter->skillCollection()->skillGainedValue((SKILL) skill) + amount);

                _logger->debug()
                    << "[813C] void critter_mod_skill(GameCritterObject* who, int skill, int amount)" << std::endl
                    << "    skill = " << skill << std::endl
                    << "    amount = " << amount << std::endl
                ;
            }
        }
    }
}
