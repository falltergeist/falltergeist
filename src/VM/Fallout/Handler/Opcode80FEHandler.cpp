#include "Opcode80FEHandler.h"
#include "Game/DudeObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FE::applyTo(std::shared_ptr<IContext> context)
            {
                auto &debug = Logger::debug("SCRIPT");
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
