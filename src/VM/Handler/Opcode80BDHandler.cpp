// Project includes
#include "../../VM/Handler/Opcode80BDHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BD::Opcode80BD(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80BD::_run()
            {
                logger->debug() << "[80BD] [=] void* source_obj()" << std::endl;
                _script->dataStack()->push(_script->sourceObject());
            }
        }
    }
}


