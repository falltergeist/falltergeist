// Project includes
#include "../../VM/Handler/Opcode8030Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8030::Opcode8030(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8030::_run(VM::Script& script)
            {
                _logger->debug() << "[8030] [*] op_while(address, condition)" << std::endl;
                auto condition = script.dataStack()->popLogical();
                if (!condition) {
                    script.setProgramCounter(script.dataStack()->popInteger());
                }
            }
        }
    }
}
