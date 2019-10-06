#include "Opcode80E8Handler.h"
#include "Game/CritterObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80E8::applyTo(std::shared_ptr<IContext> context)
            {
                auto &debug = Logger::debug("SCRIPT") << "[80E8] [+] void critter_heal(ObjectPtr who, int amount)"
                                                      << std::endl;
                int amount = _script->dataStack()->popInteger();
                debug << "    amount = " << amount << std::endl;
                auto critter = dynamic_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                if (!critter) {
                    _error("VM::critter_heal - invalid critter pointer");
                }
                critter->setHitPoints(critter->hitPoints() + amount);
            }
        }
    }
}
