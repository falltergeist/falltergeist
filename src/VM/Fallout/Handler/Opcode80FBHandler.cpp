#include "Opcode80FBHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FB::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80FB] [=] int critter_state(void* who)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
