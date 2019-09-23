#include "../../VM/Handler/Opcode8149Handler.h"
#include "../../Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8149::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // TODO: should it return FID of current animation?
                Logger::debug("SCRIPT") << "[8149] [+] int obj_art_fid(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                _script->dataStack()->push(object->FID());
            }
        }
    }
}
