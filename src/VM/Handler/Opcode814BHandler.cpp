#include "../../VM/Handler/Opcode814BHandler.h"
#include "../../Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode814B::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                // @TODO
                Logger::debug("SCRIPT") << "[814B] [*] void* party_member_obj(int pid)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->push((Game::Object *) nullptr);
            }
        }
    }
}

