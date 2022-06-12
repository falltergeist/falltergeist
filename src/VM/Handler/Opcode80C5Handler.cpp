// Project includes
#include "../../VM/Handler/Opcode80C5Handler.h"
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
            Opcode80C5::Opcode80C5(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80C5::_run(VM::Script& script)
            {
                auto &debug = _logger->debug();
                debug << "[80C5] [?] GVAR[num]" << std::endl;
                int num = script.dataStack()->popInteger();
                int value = 0;
                if (num < 0) {
                    value = 0;
                } else {
                    auto game = Game::Game::getInstance();
                    value = game->GVAR(num);
                }
                script.dataStack()->push(value);

                debug << "    num = 0x" << std::hex << num << std::endl;
                debug << "    value = 0x" << std::hex << value << std::endl;
            }
        }
    }
}


