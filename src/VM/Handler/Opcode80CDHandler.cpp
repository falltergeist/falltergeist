#include "../../VM/Handler/Opcode80CDHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CD::Opcode80CD(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80CD::_run()
            {
                logger->debug() << "[80CD] [=] void animate_stand_reverse_obj(void* obj)" << std::endl;
                _script->dataStack()->popObject();
            }
        }
    }
}
