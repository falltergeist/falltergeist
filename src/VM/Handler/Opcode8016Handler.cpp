// Project includes
#include "../../VM/Handler/Opcode8016Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8016::Opcode8016(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8016::_run()
            {
                auto name = _script->dataStack()->popString();
                auto EVARS = Game::Game::getInstance()->locationState()->EVARS();
                if (EVARS->find(name) == EVARS->end()) {
                    EVARS->insert(std::make_pair(name, StackValue(0)));
                }
                logger->debug()
                    << "[8016] [*] op_export_var(name)" << std::endl
                    << "    name: " << name << std::endl
                ;
            }
        }
    }
}
