// Project includes
#include "../../VM/Handler/Opcode8122Handler.h"
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
            Opcode8122::Opcode8122(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8122::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[8122] [+] void poison(GameCritterObject* who, int amount)" << std::endl;
                int amount = script.dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto critter = dynamic_cast<Game::CritterObject *>(script.dataStack()->popObject());
                if (!critter) {
                    _error("poison - WHO is not critter");
                }
                critter->setPoisonLevel(critter->poisonLevel() + amount);
            }
        }
    }
}
