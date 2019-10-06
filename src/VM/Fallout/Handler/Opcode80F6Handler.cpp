#include "Opcode80F6Handler.h"
#include "Game/Game.h"
#include "Game/Time.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F6::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80F6] [*] int game_time_hour" << std::endl;
                unsigned int hours = Game::getInstance()->gameTime()->hours();
                unsigned int minutes = Game::getInstance()->gameTime()->minutes();

                _script->dataStack()->push(hours * 100 + minutes);
            }
        }
    }
}


