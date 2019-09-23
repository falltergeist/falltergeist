#include "../../VM/Handler/Opcode8150Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8150::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[8150] [=] int obj_on_screen(void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(1);
            }
        }
    }
}
