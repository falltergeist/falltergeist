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
            Opcode80CB::Opcode80CB(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80CB::_run()
            {
                logger->debug()
                    << "[80CB] [+] int set_critter_stat(GameCritterObject* who, int number, int value)"
                    << std::endl
                ;
                int value = _script->dataStack()->popInteger();
                int number = _script->dataStack()->popInteger();
                if (number > 6) {
                    _error("set_critter_stat - number out of range:" + std::to_string(number));
                }
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("set_critter_stat(who, num, value) - who is null");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (!critter) {
                    _error("set_critter_stat(who, num, value) - who is not a critter");
                }
                critter->setStat((STAT) number, value);
                if (dynamic_cast<Game::DudeObject *>(critter)) {
                    _script->dataStack()->push(3); // for dude
                } else {
                    _script->dataStack()->push(-1); // for critter
                }
            }
        }
    }
}
