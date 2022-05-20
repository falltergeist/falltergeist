#include "../../VM/Handler/Opcode8150Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8150::Opcode8150(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8150::_run()
            {
                logger->debug() << "[8150] [=] int obj_on_screen(void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(1);
            }
        }
    }
}
