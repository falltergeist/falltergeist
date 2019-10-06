#include "Opcode80DAHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80DA::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80DA] [=] void wield_obj_critter(void* who, void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}
