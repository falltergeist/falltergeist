#include "../../VM/Handler/Opcode8133Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8133::Opcode8133(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8133::_run()
            {
                logger->debug() << "[8134] [=] void game_ui_disable()" << std::endl;
            }
        }
    }
}
