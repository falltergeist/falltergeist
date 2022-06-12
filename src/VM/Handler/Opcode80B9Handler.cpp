// Project includes
#include "../../VM/Handler/Opcode80B9Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B9::Opcode80B9(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80B9::_run(VM::Script& script)
            {
                _logger->debug() << "[80B9] script_overrides" << std::endl;
                script.setOverrides(true);
            }
        }
    }
}
