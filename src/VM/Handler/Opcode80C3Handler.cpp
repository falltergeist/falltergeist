#include "../../VM/Handler/Opcode80C3Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C3::Opcode80C3(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C3::_run()
            {
                logger->debug() << "[80C3] [?] MVAR[num]" << std::endl;
                auto num = _script->dataStack()->popInteger();
                if (num < 0) {
                    _script->dataStack()->push(0);
                }
                auto game = Game::Game::getInstance();
                _script->dataStack()->push(game->locationState()->MVAR(num));
            }
        }
    }
}
