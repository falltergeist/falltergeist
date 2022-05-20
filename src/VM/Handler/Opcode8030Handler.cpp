#include "../../VM/Handler/Opcode8030Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8030::Opcode8030(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8030::_run()
            {
                logger->debug() << "[8030] [*] op_while(address, condition)" << std::endl;
                auto condition = _script->dataStack()->popLogical();
                if (!condition) {
                    _script->setProgramCounter(_script->dataStack()->popInteger());
                }
            }
        }
    }
}
