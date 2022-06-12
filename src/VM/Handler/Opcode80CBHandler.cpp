// Project includes
#include "../../VM/Handler/Opcode80CBHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/DudeObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CB::Opcode80CB(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80CB::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80CB] [+] int set_critter_stat(GameCritterObject* who, int number, int value)"
                    << std::endl
                ;
                int value = script.dataStack()->popInteger();
                int number = script.dataStack()->popInteger();
                if (number > 6) {
                    _error("set_critter_stat - number out of range:" + std::to_string(number));
                }
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("set_critter_stat(who, num, value) - who is null");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (!critter) {
                    _error("set_critter_stat(who, num, value) - who is not a critter");
                }
                critter->setStat((STAT) number, value);
                if (dynamic_cast<Game::DudeObject *>(critter)) {
                    script.dataStack()->push(3); // for dude
                } else {
                    script.dataStack()->push(-1); // for critter
                }
            }
        }
    }
}
