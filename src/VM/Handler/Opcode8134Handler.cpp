#include "../../VM/Handler/Opcode8134Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8134::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[8134] [=] void game_ui_enable()" << std::endl;
            }
        }
    }
}
