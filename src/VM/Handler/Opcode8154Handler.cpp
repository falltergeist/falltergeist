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
            Opcode8154::Opcode8154(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8154::_run()
            {
                logger->debug() << "[8154] [*] void debug(string*)" << std::endl;
                auto value = _script->dataStack()->pop();
                logger->debug() << value.toString() << std::endl;
            }
        }
    }
}
