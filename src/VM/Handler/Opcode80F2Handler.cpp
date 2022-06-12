// Project includes
#include "../../VM/Handler/Opcode80F2Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F2::Opcode80F2(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F2::_run(VM::Script& script)
            {
                _logger->debug() << "[80F2] [=] int game_ticks(int seconds)" << std::endl;
                auto seconds = script.dataStack()->popInteger();
                // one second equals 10 game ticks
                script.dataStack()->push(seconds * 10);
            }
        }
    }
}
