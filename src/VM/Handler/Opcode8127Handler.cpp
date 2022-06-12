// Project includes
#include "../../VM/Handler/Opcode8127Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8127::Opcode8127(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8127::_run(VM::Script& script)
            {
                _logger->debug() << "[8127] [*] void critter_injure(ObjectPtr who, int how)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}
