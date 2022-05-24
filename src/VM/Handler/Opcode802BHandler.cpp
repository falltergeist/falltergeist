// Project includes
#include "../../VM/Handler/Opcode802BHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802B::Opcode802B(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode802B::_run()
            {
                auto argumentsCounter = _script->dataStack()->popInteger();
                _script->returnStack()->push(static_cast<unsigned>(_script->DVARbase()));
                _script->setDVARBase(_script->dataStack()->size() - argumentsCounter);
                logger->debug() << "[802B] [*] op_push_base = " << _script->DVARbase() << std::endl;
            }

        }
    }
}
