#include "Opcode80E7Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80E7::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80E7] [=] int anim_busy(void* obj)" << std::endl;
                _script->dataStack()->popObject();//auto object = (GameObject*)popDataPointer();
                //pushDataInteger(object->animationQueue()->enabled());
                _script->dataStack()->push(1);
            }
        }
    }
}
