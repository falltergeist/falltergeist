// Project includes
#include "../../VM/Handler/Opcode80B0Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B0::Opcode80B0(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80B0::_run(VM::Script& script)
            {
                _logger->debug() << "[80B0] [*] int is_critical(int val)" << std::endl;
                auto value = script.dataStack()->popInteger();
                if (value == 0 || value == 3) {
                    script.dataStack()->push(1);
                } else {
                    script.dataStack()->push(0);
                }
            }
        }
    }
}


