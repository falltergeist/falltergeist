// Project includes
#include "../../VM/Handler/Opcode80EEHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80EE::Opcode80EE(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80EE::_run(VM::Script& script)
            {
                _logger->debug() << "[80EE] [=] void kill_critter_type(int pid)" << std::endl;
                script.dataStack()->popInteger();
            }
        }
    }
}
