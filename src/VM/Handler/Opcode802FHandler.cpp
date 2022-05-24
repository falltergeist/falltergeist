// Project includes
#include "../../VM/Handler/Opcode802FHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802F::Opcode802F(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode802F::_run()
            {
                auto condition = _script->dataStack()->popLogical();
                auto address = _script->dataStack()->popInteger();
                logger->debug()
                    << "[802F] [*] op_if(address, condition) " << std::hex
                    << _script->programCounter() << std::endl
                    << "    address = " << std::hex << address << std::endl
                    << "    condition = " << std::dec << condition << std::endl
                ;
                if (!condition) {
                    _script->setProgramCounter(address);
                }
            }
        }
    }
}
