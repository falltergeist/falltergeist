// Project includes
#include "../../VM/Handler/Opcode801CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801C::Opcode801C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode801C::_run(VM::Script& script)
            {
                script.setProgramCounter(script.returnStack()->popInteger());
                _logger->debug()
                    << "[801C] [*] op_pop_return 0x" << std::hex << script.programCounter()
                    << std::endl
                ;
            }
        }
    }
}
