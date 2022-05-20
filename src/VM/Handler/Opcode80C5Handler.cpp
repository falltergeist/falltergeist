#include "../../VM/Handler/Opcode80C5Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C5::Opcode80C5(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C5::_run()
            {
                auto &debug = logger->debug();
                debug << "[80C5] [?] GVAR[num]" << std::endl;
                int num = _script->dataStack()->popInteger();
                int value = 0;
                if (num < 0) {
                    value = 0;
                } else {
                    auto game = Game::Game::getInstance();
                    value = game->GVAR(num);
                }
                _script->dataStack()->push(value);

                debug << "    num = 0x" << std::hex << num << std::endl;
                debug << "    value = 0x" << std::hex << value << std::endl;
            }
        }
    }
}


