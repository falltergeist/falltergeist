#include "Opcode80EFHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80EF::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80EF] void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)"
                                        << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}


