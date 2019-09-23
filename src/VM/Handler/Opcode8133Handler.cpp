#include "../../VM/Handler/Opcode8133Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8133::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[8134] [=] void game_ui_disable()" << std::endl;
            }
        }
    }
}
