// Project includes
#include "../../VM/Handler/Opcode80B8Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B8::Opcode80B8(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B8::_run()
            {
                logger->debug() << "[80B8] [*] void display_msg(string)" << std::endl;
                auto value = _script->dataStack()->pop();
                auto game = Game::Game::getInstance();
                game->locationState()->displayMessage(value.toString());
            }
        }
    }
}
