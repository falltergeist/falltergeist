// Project includes
#include "../../VM/Handler/Opcode80FEHandler.h"
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
            Opcode80FE::Opcode80FE(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80FE::_run(VM::Script& script) {
                auto &debug = _logger->debug();
                debug << "[80FE] [+] void radiation_dec(GameObject* who, int amount)" << std::endl;
                int amount = script.dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("radiation_dec - object is NULL");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (critter) {
                    critter->setRadiationLevel(critter->radiationLevel() - amount);
                } else {
                    _warning(script, "radiation_dec - object is not critter");
                }
            }
        }
    }
}
