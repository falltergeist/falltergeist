#include "Opcode8139Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8139::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[8139] [=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}


