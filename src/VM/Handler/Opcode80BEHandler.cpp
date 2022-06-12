// Project includes
#include "../../VM/Handler/Opcode80BEHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BE::Opcode80BE(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80BE::_run(VM::Script& script)
            {
                _logger->debug() << "[80BE/80C0] [=] object target_obj/obj_being_used_with()" << std::endl;
                script.dataStack()->push(script.targetObject());
            }
        }
    }
}
