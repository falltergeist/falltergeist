// Project includes
#include "../../VM/Handler/Opcode8115Handler.h"
#include "../../Game/Game.h"
#include "../../State/Movie.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8115::Opcode8115(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8115::_run(VM::Script& script)
            {
                _logger->debug() << "[8115] [*] void playMovie(int movie)" << std::endl;
                int movie = script.dataStack()->popInteger();
                auto state = new State::Movie(movie);
                Game::Game::getInstance()->pushState(state);
            }
        }
    }
}
