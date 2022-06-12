// Project includes
#include "../../VM/Handler/Opcode802FHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802F::Opcode802F(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode802F::_run(VM::Script& script)
            {
                auto condition = script.dataStack()->popLogical();
                auto address = script.dataStack()->popInteger();
                _logger->debug()
                    << "[802F] [*] op_if(address, condition) " << std::hex
                    << script.programCounter() << std::endl
                    << "    address = " << std::hex << address << std::endl
                    << "    condition = " << std::dec << condition << std::endl
                ;
                if (!condition) {
                    script.setProgramCounter(address);
                }
            }
        }
    }
}
