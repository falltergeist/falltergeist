// Project includes
#include "../../VM/Handler/Opcode8010Handler.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8010::Opcode8010(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8010::_run(VM::Script& script)
            {
                _logger->debug() << "[8010] [*] op_exit_prog" << std::endl;
                script.setInitialized(true);
                throw VM::HaltException();
            }
        }
    }
}
