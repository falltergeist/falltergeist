// Project includes
#include "../../VM/Handler/Opcode80C4Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
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
            Opcode80C4::Opcode80C4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C4::_run(VM::Script& script)
            {
                _logger->debug() << "[80C4] [+] MVAR[num] = value" << std::endl;
                auto value = script.dataStack()->popInteger();
                auto num = script.dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                game->locationState()->setMVAR(num, value);
            }
        }
    }
}
