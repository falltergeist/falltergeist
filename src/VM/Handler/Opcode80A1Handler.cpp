// Project includes
#include "../../VM/Handler/Opcode80A1Handler.h"
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
            Opcode80A1::Opcode80A1(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A1::_run(VM::Script& script)
            {
                _logger->debug() << "[80A1] [+] void give_exp_points(int points)" << std::endl;
                auto points = script.dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                game->player()->setExperience(game->player()->experience() + points);
            }
        }
    }
}
