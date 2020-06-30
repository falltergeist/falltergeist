#include "../../VM/Handler/Opcode80CCHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CC::Opcode80CC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80CC::_run()
            {
                logger->debug() << "[80CC] [=] void animate_stand_obj(void* obj)" << std::endl;
                _script->dataStack()->popObject();
            }
        }
    }
}
