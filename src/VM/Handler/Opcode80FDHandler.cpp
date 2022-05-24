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
            Opcode80FD::Opcode80FD(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80FD::_run()
            {
                auto &debug = logger->debug();
                debug << "[80FD] [+] void radiation_inc(GameObject* who, int amount)" << std::endl;
                int amount = _script->dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("radiation_inc - object is NULL");
                }
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                if (critter) {
                    critter->setRadiationLevel(critter->radiationLevel() + amount);
                } else {
                    _warning("radiation_inc - object is not critter");
                }
            }
        }
    }
}
