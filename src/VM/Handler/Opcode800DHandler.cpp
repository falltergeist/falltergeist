// Project includes
#include "../../VM/Handler/Opcode800DHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode800D::Opcode800D(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode800D::_run()
            {
                logger->debug() << "[800D] [*] op_d_to_a" << std::endl;
                _script->returnStack()->push(_script->dataStack()->pop());
            }
        }
    }
}
