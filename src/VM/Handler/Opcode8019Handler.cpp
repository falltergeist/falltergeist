#include "../../VM/Handler/Opcode8019Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8019::Opcode8019(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8019::_run()
            {
                logger->debug() << "[8019] [*] op_swapa" << std::endl;
                _script->returnStack()->swap();
            }
        }
    }
}
