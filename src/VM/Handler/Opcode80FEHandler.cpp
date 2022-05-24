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
            Opcode80FE::Opcode80FE(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80FE::_run() {
                auto &debug = logger->debug();
                debug << "[80FE] [+] void radiation_dec(GameObject* who, int amount)" << std::endl;
                int amount = _script->dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("radiation_dec - object is NULL");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (critter) {
                    critter->setRadiationLevel(critter->radiationLevel() - amount);
                } else {
                    _warning("radiation_dec - object is not critter");
                }
            }
        }
    }
}
