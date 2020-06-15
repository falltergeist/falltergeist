#include "../../VM/Handler/Opcode802CHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802C::Opcode802C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode802C::_run()
            {
                _script->setSVARbase(static_cast<int>(_script->dataStack()->size()));
                logger->debug() << "[802C] [*] op_set_global = " << _script->SVARbase() << std::endl;
            }
        }
    }
}
