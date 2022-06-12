// Project includes
#include "../../VM/Handler/Opcode80C3Handler.h"
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
            Opcode80C3::Opcode80C3(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C3::_run(VM::Script& script)
            {
                _logger->debug() << "[80C3] [?] MVAR[num]" << std::endl;
                auto num = script.dataStack()->popInteger();
                if (num < 0) {
                    script.dataStack()->push(0);
                }
                auto game = Game::Game::getInstance();
                script.dataStack()->push(game->locationState()->MVAR(num));
            }
        }
    }
}
