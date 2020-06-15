#include "../../VM/Handler/Opcode814EHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode814E::Opcode814E(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode814E::_run()
            {
                logger->debug() << "[814E] [=] void gdialog_set_barter_mod(int mod)" << std::endl;
                _script->dataStack()->popInteger();
            }
        }
    }
}
