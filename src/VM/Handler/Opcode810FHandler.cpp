// Project includes
#include "../../VM/Handler/Opcode810FHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810F::Opcode810F(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode810F::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[810F] [=] void reg_anim_animate(void* what, int anim, int delay) "
                    << std::endl
                ;
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}


