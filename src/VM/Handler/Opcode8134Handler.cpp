// Project includes
#include "../../VM/Handler/Opcode8134Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8134::Opcode8134(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8134::_run()
            {
                logger->debug() << "[8134] [=] void game_ui_enable()" << std::endl;
            }
        }
    }
}
