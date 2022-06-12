// Project includes
#include "../../VM/Handler/Opcode80FDHandler.h"
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
            Opcode80FD::Opcode80FD(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80FD::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[80FD] [+] void radiation_inc(GameObject* who, int amount)" << std::endl;
                int amount = script.dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("radiation_inc - object is NULL");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (critter) {
                    critter->setRadiationLevel(critter->radiationLevel() + amount);
                } else {
                    _warning(script, "radiation_inc - object is not critter");
                }
            }
        }
    }
}
