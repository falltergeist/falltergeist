#include "Opcode80E4Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80E4::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80E4] [=] void load_map(string* map, int param)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
