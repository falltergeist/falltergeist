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
            Opcode8115::Opcode8115(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8115::_run()
            {
                logger->debug() << "[8115] [*] void playMovie(int movie)" << std::endl;
                int movie = _script->dataStack()->popInteger();
                auto state = new State::Movie(movie);
                Game::Game::getInstance()->pushState(state);
            }
        }
    }
}
