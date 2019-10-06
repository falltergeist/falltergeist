#include "Opcode80CCHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80CC::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80CC] [=] void animate_stand_obj(void* obj)" << std::endl;
                _script->dataStack()->popObject();
            }
        }
    }
}
