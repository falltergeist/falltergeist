// Project includes
#include "../../VM/Handler/Opcode8032Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8032::Opcode8032(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8032::_run()
            {
                auto num = _script->dataStack()->popInteger();
                auto value = _script->dataStack()->values()->at(_script->DVARbase() + num);
                _script->dataStack()->push(value);
                logger->debug()
                    << "[8032] [*] op_fetch " << "var" << std::hex << num << " type = "
                    << value.typeName() << std::endl
                ;
            }

        }
    }
}
