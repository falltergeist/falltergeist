#include "../../VM/Handler/Opcode8031Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8031::Opcode8031(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8031::_run()
            {
                auto num = _script->dataStack()->popInteger();
                auto value = _script->dataStack()->pop();
                logger->debug()
                    << "[8031] [*] op_store " << "var" << std::hex << num << " type = "
                    << value.typeName() << std::endl
                ;
                _script->dataStack()->values()->at(_script->DVARbase() + num) = value;
            }
        }
    }
}
