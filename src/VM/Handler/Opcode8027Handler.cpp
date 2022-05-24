// Project includes
#include "../../VM/Handler/Opcode8027Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8027::Opcode8027(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8027::_run()
            {
                logger->debug() << "[8027] [?] op_check_arg_count" << std::endl;
                _script->dataStack()->pop(); // number of actual arguments
                _script->dataStack()->pop(); // procedure index
                // @TODO: compare number of arguments with procedure info and throw script exception if they are not equal
            }
        }
    }
}
