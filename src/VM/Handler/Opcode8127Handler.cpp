#include "../../VM/Handler/Opcode8127Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8127::Opcode8127(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8127::_run()
            {
                logger->debug() << "[8127] [*] void critter_injure(ObjectPtr who, int how)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
