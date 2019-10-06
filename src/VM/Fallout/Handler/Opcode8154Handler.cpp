#include "Opcode8154Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8154::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[8154] [*] void debug(string*)" << std::endl;
                auto value = _script->dataStack()->pop();
                Logger::debug("SCRIPT") << value.toString() << std::endl;
            }
        }
    }
}
