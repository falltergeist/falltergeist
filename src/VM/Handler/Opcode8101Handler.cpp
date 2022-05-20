#include "../../VM/Handler/Opcode8101Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8101::Opcode8101(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8101::_run()
            {
                logger->debug() << "[8101] [=] int cur_map_index()" << std::endl;
                _script->dataStack()->push(Game::Game::getInstance()->locationState()->currentMapIndex());
            }
        }
    }
}
