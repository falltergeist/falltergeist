#include "../../VM/Handler/Opcode80BEHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BE::Opcode80BE(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80BE::_run()
            {
                logger->debug() << "[80BE/80C0] [=] object target_obj/obj_being_used_with()" << std::endl;
                _script->dataStack()->push(_script->targetObject());
            }
        }
    }
}
