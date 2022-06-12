// Project includes
#include "../../VM/Handler/Opcode80C6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C6::Opcode80C6(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80C6::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[80C6] [+] GVAR[num] = value" << std::endl;
                auto value = script.dataStack()->popInteger();
                auto num = script.dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                game->setGVAR(num, value);
                debug << "    num = " << num << ", value = " << value << std::endl;
            }
        }
    }
}


