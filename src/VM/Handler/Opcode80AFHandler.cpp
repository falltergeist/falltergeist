// Project includes
#include "../../VM/Handler/Opcode80AFHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AF::Opcode80AF(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80AF::_run(VM::Script& script)
            {
                _logger->debug() << "[80AF] [*] int is_success(int val)" << std::endl;
                auto value = script.dataStack()->popInteger();
                switch (value) {
                    case 0:
                    case 1:
                        script.dataStack()->push(0);
                        break;
                    case 2:
                    case 3:
                        script.dataStack()->push(1);
                        break;
                    default:
                        _error("is_success - wrong argument: " + std::to_string(value));
                        break;
                }
            }
        }
    }
}


