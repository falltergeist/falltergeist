#include "../../VM/Handler/Opcode80DAHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DA::Opcode80DA(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80DA::_run()
            {
                logger->debug() << "[80DA] [=] void wield_obj_critter(void* who, void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}
