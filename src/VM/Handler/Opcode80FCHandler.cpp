// Project includes
#include "../../VM/Handler/Opcode80FCHandler.h"
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
            Opcode80FC::Opcode80FC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80FC::_run()
            {
                int amount = _script->dataStack()->popInteger();
                logger->debug()
                    << "[80FC] [=] void game_time_advance(int amount)" << std::endl
                    << "    amount = " << amount << std::endl
                ;
                auto time = Game::Game::getInstance()->gameTime();
                for (auto i = 0; i != amount; ++i) {
                    time->increaseTicks();
                }
            }
        }
    }
}
