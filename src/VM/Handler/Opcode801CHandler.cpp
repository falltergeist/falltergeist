// Project includes
#include "../../VM/Handler/Opcode801CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801C::Opcode801C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode801C::_run()
            {
                _script->setProgramCounter(_script->returnStack()->popInteger());
                logger->debug()
                    << "[801C] [*] op_pop_return 0x" << std::hex << _script->programCounter()
                    << std::endl
                ;
            }
        }
    }
}
