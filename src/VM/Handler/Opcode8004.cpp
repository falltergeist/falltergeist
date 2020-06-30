#include "../../VM/Handler/Opcode8004.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8004::Opcode8004(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8004::_run()
            {
                auto address = _script->dataStack()->popInteger();
                logger->debug()
                    << "[8004] [*] op_jmp(address)" << std::endl
                    << "    address: " << std::hex << address << std::endl
                ;
                _script->setProgramCounter(address);
            }
        }
    }
}
