// Project includes
#include "../../VM/Handler/Opcode800CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode800C::Opcode800C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode800C::_run()
            {
                logger->debug() << "[800C] [*] op_a_to_d" << std::endl;
                _script->dataStack()->push(_script->returnStack()->pop());
            }
        }
    }
}
