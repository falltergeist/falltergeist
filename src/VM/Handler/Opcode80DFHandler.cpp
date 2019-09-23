#include "../../VM/Handler/Opcode80DFHandler.h"
#include "../../Game/Game.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80DF::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80DF] [?] end_dialogue" << std::endl;
                auto game = Game::getInstance();
                game->popState(); // interact state
            }
        }
    }
}
