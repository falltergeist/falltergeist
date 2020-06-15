#include "../../VM/Handler/Opcode80A1Handler.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A1::Opcode80A1(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80A1::_run()
            {
                logger->debug() << "[80A1] [+] void give_exp_points(int points)" << std::endl;
                auto points = _script->dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                game->player()->setExperience(game->player()->experience() + points);
            }
        }
    }
}
