// Project includes
#include "../../VM/Handler/Opcode80DFHandler.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DF::Opcode80DF(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80DF::_run(VM::Script& script)
            {
                _logger->debug() << "[80DF] [?] end_dialogue" << std::endl;
                auto game = Game::Game::getInstance();
                game->popState(); // interact state
            }
        }
    }
}
