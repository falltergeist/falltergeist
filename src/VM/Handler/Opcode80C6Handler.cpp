#include "../../VM/Handler/Opcode80C6Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C6::Opcode80C6(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C6::_run()
            {
                auto &debug = logger->debug();
                debug << "[80C6] [+] GVAR[num] = value" << std::endl;
                auto value = _script->dataStack()->popInteger();
                auto num = _script->dataStack()->popInteger();
                auto game = Game::Game::getInstance();
                game->setGVAR(num, value);
                debug << "    num = " << num << ", value = " << value << std::endl;
            }
        }
    }
}


