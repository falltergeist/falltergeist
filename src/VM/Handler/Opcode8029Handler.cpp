// Project includes
#include "../../VM/Handler/Opcode8029Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8029::Opcode8029(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8029::_run(VM::Script& script)
            {
                script.setDVARBase(static_cast<size_t>(script.returnStack()->popInteger()));
                _logger->debug() << "[8029] [*] op_pop_base " << script.DVARbase() << std::endl;
            }
        }
    }
}
