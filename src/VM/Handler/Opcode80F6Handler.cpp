// Project includes
#include "../../VM/Handler/Opcode80F6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F6::Opcode80F6(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F6::_run(VM::Script& script)
            {
                _logger->debug() << "[80F6] [*] int game_time_hour" << std::endl;
                unsigned int hours = Game::Game::getInstance()->gameTime()->hours();
                unsigned int minutes = Game::Game::getInstance()->gameTime()->minutes();

                script.dataStack()->push(hours * 100 + minutes);
            }
        }
    }
}


