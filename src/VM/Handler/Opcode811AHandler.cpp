#include "../../VM/Handler/Opcode811AHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811A::Opcode811A(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode811A::_run()
            {
                logger->debug() << "[811A] [=] int explosion(int where, int elevation, int damage)" << std::endl;
                auto damageRadius = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto tile = _script->dataStack()->popInteger();
                logger->debug() << "Triggered explosion on elevation " << elevation << " on tile " << tile << " with damage radius " << damageRadius << std::endl;
                _script->dataStack()->push(0);
            }
        }
    }
}
