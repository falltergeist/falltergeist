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
            Opcode80B4::Opcode80B4(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B4::_run()
            {
                logger->debug() << "[80B4] [+] int rand(int min, int max)" << std::endl;
                auto max = _script->dataStack()->popInteger();
                auto min = _script->dataStack()->popInteger();
                _script->dataStack()->push(rand() % (max - min + 1) + min);
            }
        }
    }
}


