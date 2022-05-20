#include "../../VM/Handler/Opcode80E7Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E7::Opcode80E7(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E7::_run()
            {
                logger->debug() << "[80E7] [=] int anim_busy(void* obj)" << std::endl;
                _script->dataStack()->popObject();//auto object = (GameObject*)popDataPointer();
                //pushDataInteger(object->animationQueue()->enabled());
                _script->dataStack()->push(1);

            }
        }
    }
}
