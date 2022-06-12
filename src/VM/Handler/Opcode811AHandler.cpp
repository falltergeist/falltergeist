// Project includes
#include "../../VM/Handler/Opcode811AHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811A::Opcode811A(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode811A::_run(VM::Script& script)
            {
                _logger->debug() << "[811A] [=] int explosion(int where, int elevation, int damage)" << std::endl;
                auto damageRadius = script.dataStack()->popInteger();
                auto elevation = script.dataStack()->popInteger();
                auto tile = script.dataStack()->popInteger();
                _logger->debug() << "Triggered explosion on elevation " << elevation << " on tile " << tile << " with damage radius " << damageRadius << std::endl;
                script.dataStack()->push(0);
            }
        }
    }
}
