#include "../../VM/Handler/Opcode814AHandler.h"
#include "../../Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode814A::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // @TODO
                Logger::debug("SCRIPT") << "[814A] [*] int art_anim(int fid)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->push(0);
            }
        }
    }
}

