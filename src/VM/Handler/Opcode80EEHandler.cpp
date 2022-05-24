// Project includes
#include "../../VM/Handler/Opcode80EEHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80EE::Opcode80EE(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80EE::_run()
            {
                logger->debug() << "[80EE] [=] void kill_critter_type(int pid)" << std::endl;
                _script->dataStack()->popInteger();
            }
        }
    }
}
