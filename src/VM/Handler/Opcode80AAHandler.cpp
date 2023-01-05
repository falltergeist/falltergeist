// Project includes
#include "../../VM/Handler/Opcode80AAHandler.h"
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
            Opcode80AA::Opcode80AA(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80AA::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[80AA] [+] int get_skill_value(GameCritterObject* who, int skill) " << std::endl;
                int skill = script.dataStack()->popInteger();
                debug << "    skill = " << skill << std::endl;
                if (skill > 17 || skill < 0) {
                    _error("get_skill_value - skill out of range: " + std::to_string(skill));
                }
                auto object = script.dataStack()->popObject();
                int value = 0;
                if (auto critter = dynamic_cast<Game::CritterObject *>(object)) {
                    value = critter->skillCollection()->skillValue((SKILL) skill);
                    script.dataStack()->push(value);
                } else {
                    _error("get_skill_value(who, skill): who is not critter");
                }
            }
        }
    }
}


