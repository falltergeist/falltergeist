// Project includes
#include "../../VM/Handler/Opcode803FHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode803F::Opcode803F(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode803F::_run()
            {
                logger->debug() << "[803F] [+] op_or" << std::endl;
                auto b = _script->dataStack()->popLogical();
                auto a = _script->dataStack()->popLogical();
                _script->dataStack()->push(a || b); // integer 1 or 0
            }
        }
    }
}
