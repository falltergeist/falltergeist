#include "../../VM/Handler/Opcode8029Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8029::Opcode8029(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8029::_run()
            {
                _script->setDVARBase(static_cast<size_t>(_script->returnStack()->popInteger()));
                logger->debug() << "[8029] [*] op_pop_base " << _script->DVARbase() << std::endl;
            }
        }
    }
}
