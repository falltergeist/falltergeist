#include "../../VM/Handler/Opcode80B0Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B0::Opcode80B0(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B0::_run()
            {
                logger->debug() << "[80B0] [*] int is_critical(int val)" << std::endl;
                auto value = _script->dataStack()->popInteger();
                if (value == 0 || value == 3) {
                    _script->dataStack()->push(1);
                } else {
                    _script->dataStack()->push(0);
                }
            }
        }
    }
}


