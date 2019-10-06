#include "Opcode814EHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode814E::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[814E] [=] void gdialog_set_barter_mod(int mod)" << std::endl;
                _script->dataStack()->popInteger();
            }
        }
    }
}
