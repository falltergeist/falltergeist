#include "Opcode80FCHandler.h"
#include "Game/Game.h"
#include "Game/Time.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FC::applyTo(std::shared_ptr<IContext> context)
            {
                int amount = _script->dataStack()->popInteger();
                Logger::debug("SCRIPT") << "[80FC] [=] void game_time_advance(int amount)" << std::endl
                                        << "    amount = " << amount << std::endl;
                auto time = Game::getInstance()->gameTime();
                for (auto i = 0; i != amount; ++i) {
                    time->increaseTicks();
                }
            }
        }
    }
}
