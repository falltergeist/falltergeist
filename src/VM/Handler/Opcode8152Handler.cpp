#include "../../VM/Handler/Opcode8152Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8152::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[8152] [=] void op_critter_set_flee_state(critter who, boolean flag)"
                                        << std::endl;
                // @TODO: add implementation
                _script->dataStack()->popLogical();
                _script->dataStack()->popObject();
            }
        }
    }
}
