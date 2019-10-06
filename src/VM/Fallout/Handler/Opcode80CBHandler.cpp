#include "Opcode80CBHandler.h"
#include "Game/CritterObject.h"
#include "Game/DudeObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80CB::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT")
                        << "[80CB] [+] int set_critter_stat(GameCritterObject* who, int number, int value)"
                        << std::endl;
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
