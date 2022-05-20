#include "../../VM/Handler/Opcode80AFHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AF::Opcode80AF(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80AF::_run()
            {
                logger->debug() << "[80AF] [*] int is_success(int val)" << std::endl;
                auto value = _script->dataStack()->popInteger();
                switch (value) {
                    case 0:
                    case 1:
                        _script->dataStack()->push(0);
                        break;
                    case 2:
                    case 3:
                        _script->dataStack()->push(1);
                        break;
                    default:
                        _error("is_success - wrong argument: " + std::to_string(value));
                        break;
                }
            }
        }
    }
}


