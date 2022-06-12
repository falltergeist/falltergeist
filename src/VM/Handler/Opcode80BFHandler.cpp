// Project includes
#include "../../VM/Handler/Opcode80BFHandler.h"
#include "../../Game/DudeObject.h"
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
            Opcode80BF::Opcode80BF(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80BF::_run(VM::Script& script)
            {
                _logger->debug() << "[80BF] [+] GameDudeObject* dude_obj()" << std::endl;
                auto game = Game::Game::getInstance();
                script.dataStack()->push(game->player().get());
            }
        }
    }
}
