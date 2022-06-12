// Project includes
#include "../../VM/Handler/Opcode814EHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode814E::Opcode814E(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode814E::_run(VM::Script& script)
            {
                _logger->debug() << "[814E] [=] void gdialog_set_barter_mod(int mod)" << std::endl;
                script.dataStack()->popInteger();
            }
        }
    }
}
