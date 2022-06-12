// Project includes
#include "../../VM/Handler/Opcode8154Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8154::Opcode8154(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8154::_run(VM::Script& script)
            {
                _logger->debug() << "[8154] [*] void debug(string*)" << std::endl;
                auto value = script.dataStack()->pop();
                _logger->debug() << value.toString() << std::endl;
            }
        }
    }
}
