#include "Opcode8143Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8143::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[8143] [=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}
