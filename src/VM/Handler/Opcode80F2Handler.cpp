#include "../../VM/Handler/Opcode80F2Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F2::Opcode80F2(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F2::_run()
            {
                logger->debug() << "[80F2] [=] int game_ticks(int seconds)" << std::endl;
                auto seconds = _script->dataStack()->popInteger();
                // one second equals 10 game ticks
                _script->dataStack()->push(seconds * 10);
            }
        }
    }
}
