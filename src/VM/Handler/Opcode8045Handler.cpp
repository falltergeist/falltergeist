// Project includes
#include "../../VM/Handler/Opcode8045Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8045::Opcode8045(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8045::_run()
            {
                logger->debug() << "[8045] [*] op_not" << std::endl;
                auto a = _script->dataStack()->popLogical();
                _script->dataStack()->push((int) (!a));
            }
        }
    }
}
