// Project includes
#include "../../VM/Handler/Opcode80BCHandler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BC::Opcode80BC(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80BC::_run(VM::Script& script)
            {
                _logger->debug() << "[80BC] [+] GameObject* self_obj()" << std::endl;
                script.dataStack()->push(script.owner());
            }
        }
    }
}
