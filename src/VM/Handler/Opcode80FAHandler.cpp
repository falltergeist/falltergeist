// Project includes
#include "../../VM/Handler/Opcode80FAHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80FA::Opcode80FA(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80FA::_run(VM::Script& script)
            {
                _logger->debug() << "[80FA] [+] int action_being_used()" << std::endl;
                script.dataStack()->push((signed) script.usedSkill());
            }
        }
    }
}
