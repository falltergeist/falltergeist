// Project includes
#include "../../VM/Handler/Opcode8138Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8138::Opcode8138(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8138::_run()
            {
                logger->debug() << "[8138] [=] int item_caps_total(void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
