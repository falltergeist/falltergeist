// Project includes
#include "../../VM/Handler/Opcode80B4Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib
#include <cstdlib>
#include <ctime>

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B4::Opcode80B4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80B4::_run(VM::Script& script)
            {
                _logger->debug() << "[80B4] [+] int rand(int min, int max)" << std::endl;
                auto max = script.dataStack()->popInteger();
                auto min = script.dataStack()->popInteger();
                script.dataStack()->push(rand() % (max - min + 1) + min);
            }
        }
    }
}


