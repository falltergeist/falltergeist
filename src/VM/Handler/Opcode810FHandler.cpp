#include "../../VM/Handler/Opcode810FHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810F::Opcode810F(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode810F::_run()
            {
                logger->debug()
                    << "[810F] [=] void reg_anim_animate(void* what, int anim, int delay) "
                    << std::endl
                ;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}


