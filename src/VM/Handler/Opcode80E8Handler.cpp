// Project includes
#include "../../VM/Handler/Opcode80E8Handler.h"
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
            Opcode80E8::Opcode80E8(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E8::_run()
            {
                auto &debug = logger->debug()
                    << "[80E8] [+] void critter_heal(ObjectPtr who, int amount)"
                    << std::endl
                ;
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
