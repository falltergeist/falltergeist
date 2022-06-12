// Project includes
#include "../../VM/Handler/Opcode80E7Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E7::Opcode80E7(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80E7::_run(VM::Script& script)
            {
                _logger->debug() << "[80E7] [=] int anim_busy(void* obj)" << std::endl;
                script.dataStack()->popObject();//auto object = (GameObject*)popDataPointer();
                //pushDataInteger(object->animationQueue()->enabled());
                script.dataStack()->push(1);

            }
        }
    }
}
