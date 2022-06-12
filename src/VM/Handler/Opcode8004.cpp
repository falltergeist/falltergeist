// Project includes
#include "../../VM/Handler/Opcode8004.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8004::Opcode8004(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8004::_run(VM::Script& script)
            {
                auto address = script.dataStack()->popInteger();
                _logger->debug()
                    << "[8004] [*] op_jmp(address)" << std::endl
                    << "    address: " << std::hex << address << std::endl
                ;
                script.setProgramCounter(address);
            }
        }
    }
}
