// Project includes
#include "../../VM/Handler/Opcode8101Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8101::Opcode8101(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8101::_run(VM::Script& script)
            {
                _logger->debug() << "[8101] [=] int cur_map_index()" << std::endl;
                script.dataStack()->push(Game::Game::getInstance()->locationState()->currentMapIndex());
            }
        }
    }
}
