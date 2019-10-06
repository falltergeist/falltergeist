#include "Opcode80F2Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F2::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80F2] [=] int game_ticks(int seconds)" << std::endl;
                auto seconds = _script->dataStack()->popInteger();
                // one second equals 10 game ticks
                _script->dataStack()->push(seconds * 10);
            }
        }
    }
}
