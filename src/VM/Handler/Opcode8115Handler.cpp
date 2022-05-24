#include "../../VM/Handler/Opcode8115Handler.h"
#include "../../Game/Game.h"
#include "../../State/Movie.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8115::Opcode8115(
                VM::Script *script,
                std::shared_ptr<ILogger> logger
            ) : OpcodeHandler(script), _logger(logger) {
            }

            void Opcode8115::_run()
            {
                _logger->debug() << "[8115] [*] void playMovie(int movie)" << std::endl;
                int movie = _script->dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                auto state = new State::Movie(game->mouse(), movie);
                game->pushState(state);
            }
        }
    }
}
