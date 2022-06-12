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
            Opcode80BD::Opcode80BD(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80BD::_run(VM::Script& script)
            {
                _logger->debug() << "[80BD] [=] void* source_obj()" << std::endl;
                script.dataStack()->push(script.sourceObject());
            }
        }
    }
}


