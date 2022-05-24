// Project includes
#include "../../VM/Handler/Opcode8139Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8139::Opcode8139(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8139::_run()
            {
                logger->debug() << "[8139] [=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}


