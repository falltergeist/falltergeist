// Project includes
#include "../../VM/Handler/Opcode802AHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802A::Opcode802A(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode802A::_run()
            {
                logger->debug() << "[802A] [*] op_pop_to_base" << std::endl;
                while (_script->dataStack()->size() > _script->DVARbase()) {
                    _script->dataStack()->pop();
                }
            }

        }
    }
}
